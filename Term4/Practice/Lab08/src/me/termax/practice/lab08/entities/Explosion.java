package me.termax.practice.lab08.entities;

import me.termax.practice.lab08.Assets;
import me.termax.practice.lab08.Settings;

import java.awt.*;
import java.util.Timer;
import java.util.TimerTask;

public class Explosion extends Entity {


    public Explosion(float x, float y, boolean visible) {
        super(x, y, visible);
        this.texture = Assets.explosion;
        Timer explosionTimer = new Timer();
        explosionTimer.schedule(new TimerTask() {
            @Override
            public void run() {
                Explosion.super.visible = false;
            }
        }, Settings.EXPLOSION_DURATION);
        Assets.playSound("duckhit", false);

    }

    @Override
    public void tick() {

    }

    @Override
    public void render(Graphics g) {
        if (visible)
            g.drawImage(texture,  (int) x, (int) y,null);
    }

}
