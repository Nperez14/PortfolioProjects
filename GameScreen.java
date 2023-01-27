package com.example.gamescreen;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Random;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GameScreen extends JPanel implements ActionListener {
    static final int SCREEN_WIDTH = 1300;
    static final int SCREEN_HEIGHT = 750;
    static final int UNIT_SIZE = 50;
    static final int GAME_UNITS = (SCREEN_WIDTH*SCREEN_HEIGHT)/(UNIT_SIZE*UNIT_SIZE);
    static final int DELAY = 175;
    final int x[] = new int[GAME_UNITS];
    final int y[] = new int[GAME_UNITS];
    int bodyParts = 6;
    int coinsTaken;
    int coinX;
    int coinY;
    char direction = 'R';
    boolean running = false;
    Timer timer;
    Random random;

    public GameScreen(){
        random = new Random();
        this.setPreferredSize(new Dimension(SCREEN_WIDTH,SCREEN_HEIGHT));
        this.setBackground(Color.black);
        this.setFocusable(true);
        this.addKeyListener(new MyKeyAdapter());
        startGame();
    }
    public void startGame() {
        newCoin();
        running = true;
        timer = new Timer(DELAY,this);
        timer.start();
    }
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        draw(g);
    }
    public void draw(Graphics g) {

        if(running) {
            g.setColor(Color.yellow);
            g.fillOval(coinX, coinY, UNIT_SIZE, UNIT_SIZE);

            for(int i = 0; i< bodyParts;i++) {
                if(i == 0) {
                    g.setColor(Color.green);
                    g.fillRect(x[i], y[i], UNIT_SIZE, UNIT_SIZE);
                }
                else {
                    g.setColor(new Color(45,180,0));
                    g.fillRect(x[i], y[i], UNIT_SIZE, UNIT_SIZE);
                }
            }
            g.setColor(Color.yellow);
            g.setFont( new Font("Times New Roman",Font.BOLD, 40));
            FontMetrics metrics = getFontMetrics(g.getFont());
            g.drawString("Score: "+coinsTaken, (SCREEN_WIDTH - metrics.stringWidth("Score: "+coinsTaken))/2, g.getFont().getSize());
        }
        else {
            gameOver(g);
        }

    }
    public void newCoin(){
        coinX = random.nextInt((int)(SCREEN_WIDTH/UNIT_SIZE))*UNIT_SIZE;
        coinY = random.nextInt((int)(SCREEN_HEIGHT/UNIT_SIZE))*UNIT_SIZE;
    }
    public void move(){
        for(int i = bodyParts;i>0;i--) {                  //positioning of the head
            x[i] = x[i-1];
            y[i] = y[i-1];
        }

        switch(direction) {                              //positioning of the body
            case 'U':
                y[0] = y[0] - UNIT_SIZE;
                break;
            case 'D':
                y[0] = y[0] + UNIT_SIZE;
                break;
            case 'L':
                x[0] = x[0] - UNIT_SIZE;
                break;
            case 'R':
                x[0] = x[0] + UNIT_SIZE;
                break;
        }

    }
    public void checkCoin() {                                     //checkcoin method to keep track of coin value
        if((x[0] == coinX) && (y[0] == coinY)) {
            bodyParts++;
            coinsTaken++;
            newCoin();
        }
    }
    public void checkCollisions() {

        for(int i = bodyParts;i>0;i--) {                    //Check if any body parts touch the edge
            if((x[0] == x[i])&& (y[0] == y[i])) {
                running = false;
            }
        }

        if(x[0] < 0) {
            running = false;
        }

        if(x[0] > SCREEN_WIDTH) {
            running = false;
        }

        if(y[0] < 0) {
            running = false;
        }

        if(y[0] > SCREEN_HEIGHT) {
            running = false;
        }

        if(!running) {
            timer.stop();
        }
    }
    public void gameOver(Graphics g) {
        //Score
        g.setColor(Color.red);
        g.setFont( new Font("Ink Free",Font.BOLD, 40));
        FontMetrics metrics1 = getFontMetrics(g.getFont());
        g.drawString("Score: "+coinsTaken, (SCREEN_WIDTH - metrics1.stringWidth("Score: "+coinsTaken))/2, g.getFont().getSize());
        //Game Over text
        g.setColor(Color.red);
        g.setFont( new Font("Ink Free",Font.BOLD, 75));
        FontMetrics metrics2 = getFontMetrics(g.getFont());
        g.drawString("Game Over", (SCREEN_WIDTH - metrics2.stringWidth("Game Over"))/2, SCREEN_HEIGHT/2);
    }
    @Override
    public void actionPerformed(ActionEvent e) {

        if(running) {
            move();
            checkCoin();
            checkCollisions();
        }
        repaint();
    }

    public class MyKeyAdapter extends KeyAdapter{
        @Override
        public void keyPressed(KeyEvent e) {
            switch(e.getKeyCode()) {
                case KeyEvent.VK_LEFT:
                    if(direction != 'R') {
                        direction = 'L';
                    }
                    break;
                case KeyEvent.VK_RIGHT:
                    if(direction != 'L') {
                        direction = 'R';
                    }
                    break;
                case KeyEvent.VK_UP:
                    if(direction != 'D') {
                        direction = 'U';
                    }
                    break;
                case KeyEvent.VK_DOWN:
                    if(direction != 'U') {
                        direction = 'D';
                    }
                    break;
            }
        }
    }
}




