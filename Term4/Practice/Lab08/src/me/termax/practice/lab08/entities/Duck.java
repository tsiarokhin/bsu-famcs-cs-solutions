package me.termax.practice.lab08.entities;

import me.termax.practice.lab08.Assets;
import me.termax.practice.lab08.Game;
import me.termax.practice.lab08.Settings;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.util.Timer;
import java.util.TimerTask;

public class Duck extends Entity {
    private boolean flyLeftToRight;
    private BufferedImage texture2;

    private Game game;

    public Duck(Game game, float x, float y, boolean flyLeftToRight) {
        super(x, y, true);
        this.game = game;
        this.flyLeftToRight = flyLeftToRight;
        this.texture = Assets.duck;
        this.texture2 = Assets.duck2;
        Timer swapTexture = new Timer();
        swapTexture.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                BufferedImage temp = texture;
                texture = texture2;
                texture2 = temp;
            }
        }, Settings.DUCK_WINGS_WAVE_RATE, Settings.DUCK_WINGS_WAVE_RATE);
        Assets.playSound("duckquack", false);
    }

    @Override
    public void tick() {
        if (visible) {
            if (flyLeftToRight) {
                x += Settings.DUCK_SPEED;
                if (x > game.width)
                    visible = false;
            }
            else {
                x -= Settings.DUCK_SPEED;
                if (x < -texture.getWidth())
                    visible = false;
            }
        }
    }

    @Override
    public void render(Graphics g) {
        if (visible) {
            if (flyLeftToRight)
                g.drawImage(texture,  (int) x, (int) y,null);
            else
                g.drawImage(texture,  (int) x+texture.getWidth(), (int) y, -texture.getWidth(), texture.getHeight(), null);

        }

    }

}
