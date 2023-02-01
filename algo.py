#region imports
from AlgorithmImports import *
#endregion
import numpy as np

class BreakoutAlgo(QCAlgorithm):

    def Initialize(self):
       
        self.SetCash(100000)
        self.SetStartDate(2020,12,14)
        self.SetEndDate(2022,12,14)
        
        
        self.symbol = self.AddEquity("SPY", Resolution.Daily).Symbol
        
       
        self.lookback = 25
        
       
        self.limit, self.low = 30, 10
        
        # Price offset for stop order
        self.initialStopRisk = 0.98
        self.trailingStopRisk = 0.9
        
       
        self.Schedule.On(self.DateRules.EveryDay(self.symbol), \
                        self.TimeRules.AfterMarketOpen(self.symbol, 20), \
                        Action(self.MarketOpen))


    def OnData(self, data):
        self.Plot("Data Chart", self.symbol, self.Securities[self.symbol].Close)

    def MarketOpen(self):
        #  determine lookback length based on 30 day rate 
        close = self.History(self.symbol, 31, Resolution.Daily)["close"]
        currentvol = np.std(close[1:31])
        yesterdayvol = np.std(close[0:30])
        totalvol = (currentvol - yesterdayvol) / currentvol
        self.lookback = round(self.lookback * (1 + totalvol))
        
      
        if self.lookback > self.limit:
            self.lookback = self.limit     #check if account exceed or below lookback 
        elif self.lookback < self.low:
            self.lookback = self.low
        
        self.high = self.History(self.symbol, self.lookback, Resolution.Daily)["high"]
        
        # Buy in case of breakout
        if not self.Securities[self.symbol].Invested and \
                self.Securities[self.symbol].Close >= max(self.high[:-1]):
            self.SetHoldings(self.symbol, 1)
            self.breakout = max(self.high[:-1])
            self.highestPrice = self.breakout
        
        
        # Create trailing stop loss if invested 
        if self.Securities[self.symbol].Invested:
            
            if not self.Transactions.GetOpenOrders(self.symbol):
                self.stopMarketTicket = self.StopMarketOrder(self.symbol, \
                                        -self.Portfolio[self.symbol].Quantity, \
                                        self.initialStopRisk * self.breakout)
            
           
            if self.Securities[self.symbol].Close > self.highestPrice and \
                    self.initialStopRisk * self.breakout < self.Securities[self.symbol].Close * self.trailingStopRisk:
              
                self.highestPrice = self.Securities[self.symbol].Close
                updateFields = UpdateOrderFields()
                updateFields.StopPrice = self.Securities[self.symbol].Close * self.trailingStopRisk
                self.stopMarketTicket.Update(updateFields)
                
               
                self.Debug(updateFields.StopPrice)
            
            self.Plot("Data Chart", "Stop Price", self.stopMarketTicket.Get(OrderField.StopPrice))