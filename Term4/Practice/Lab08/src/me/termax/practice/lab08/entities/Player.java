package me.termax.practice.lab08.entities;

import me.termax.practice.lab08.Assets;
import me.termax.practice.lab08.Game;
import me.termax.practice.lab08.Settings;
import me.termax.practice.lab08.states.GameState;

import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;

public class Player extends Entity {

    private Game game;

    public Player(Game game, float x, float y) {
        super(x, y, true);
        this.speed = Settings.PLAYER_SPEED;
        this.texture = Assets.player;
        this.game = game;
    }

    @Override
    public void tick() {
        move();
        shoot();

    }

    private void move(){
        if (game.getInputManager().isLeft() && x >= 0)
            x -= speed;
        if (game.getInputManager().isRight() && x + getWidth() <= game.width)
            x += speed;
    }

    private void shoot() {
        if (game.getInputManager().isShoot()) {
            ((GameState)game.getCurrentState()).createBullet(
                    (x+texture.getWidth()/2),
                    game.height,
                    (float)game.getMousePosition().getX(),
                    (float)game.getMousePosition().getY()
            );
        }
    }

    @Override
    public void render(Graphics g) {
        if (visible) {
            double angle = Math.atan2(game.getMousePosition().getY() - game.height,
                                      game.getMousePosition().getX() - (x+texture.getWidth()/2)) + Math.PI/2;

            AffineTransform tx = AffineTransform.getRotateInstance(angle, texture.getWidth() / 2, texture.getHeight() / 2);
            AffineTransformOp op = new AffineTransformOp(tx, AffineTransformOp.TYPE_BILINEAR);

            Stroke dashed = new BasicStroke(2, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{2}, 0);
            ((Graphics2D)g).setStroke(dashed);
            g.setColor(Color.RED);
            g.drawLine((int)(x+texture.getWidth()/2), (int)game.height, (int)game.getMousePosition().getX(), (int)game.getMousePosition().getY());

            g.drawImage(op.filter(texture, null),  (int) x, (int) y,null);


        }

    }

}