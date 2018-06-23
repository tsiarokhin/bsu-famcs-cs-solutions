package me.termax.practice.lab08.entities;

import me.termax.practice.lab08.Assets;
import me.termax.practice.lab08.Game;

import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;

public class Bullet extends Entity {
    private float vx, vy, angle;
    private Game game;

    public Bullet(Game game, float x, float y, float vx, float vy, float angle,  boolean visible) {
        super(x, y, visible);
        this.game = game;
        this.vx = vx;
        this.vy = vy;
        this.angle = angle;
        texture = Assets.bullet;
        Assets.playSound("gunshot", false);
    }

    @Override
    public void tick() {
        x += vx;
        y += vy;
        if (!(x > 0 && x < game.width) || !(y > 0 && y < game.height))
            visible = false;
    }

    @Override
    public void render(Graphics g) {
        if (visible) {
            AffineTransform tx = AffineTransform.getRotateInstance(angle, texture.getWidth() / 2, texture.getHeight() / 2);
            AffineTransformOp op = new AffineTransformOp(tx, AffineTransformOp.TYPE_BILINEAR);

            g.drawImage(op.filter(texture, null), (int) x, (int) y, null);
        }
    }
}
