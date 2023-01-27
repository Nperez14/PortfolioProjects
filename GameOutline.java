package com.example.gameoutline;

import com.example.gamescreen.GameScreen;

import javax.swing.*;

public class GameOutline extends JFrame {
    public GameOutline(){
        this.add(new GameScreen());
        this.setTitle("Snake");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setResizable(false);
        this.pack();
        this.setVisible(true);
        this.setLocationRelativeTo(null);
    }
}
