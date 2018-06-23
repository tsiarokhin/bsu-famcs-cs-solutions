package me.termax.practice.lab08.entities;

import me.termax.practice.lab08.Settings;

import java.awt.*;
import java.awt.image.BufferedImage;

public abstract class Entity {

    protected BufferedImage texture;
    protected float x, y;
    protected float speed;
    protected boolean visible;


    public Entity(float x, float y, boolean visible){
        this.x = x;
        this.y = y;
        this.visible = visible;
        this.speed = Settings.ENTITY_DEFAULT_SPEED;
    }

    public abstract void tick();

    public abstract void render(Graphics g);

    public float getX() {
        return x;
    }

    public void setX(float x) {
        this.x = x;
    }

    public float getY() {
        return y;
    }

    public void setY(float y) {
        this.y = y;
    }

    public float getSpeed() {
        return speed;
    }

    public void setSpeed(float speed) {
        this.speed = speed;
    }

    public boolean isVisible(){
        return visible;
    }

    public void setVisible(boolean visible) {
        this.visible = visible;
    }

    public int getWidth(){
        return texture.getWidth();
    }
    public int getHeight(){
        return texture.getHeight();
    }
}
