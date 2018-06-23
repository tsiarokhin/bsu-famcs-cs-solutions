package me.termax.practice.lab08.states;

import me.termax.practice.lab08.Assets;
import me.termax.practice.lab08.Game;
import me.termax.practice.lab08.Settings;
import me.termax.practice.lab08.entities.Bullet;
import me.termax.practice.lab08.entities.Duck;
import me.termax.practice.lab08.entities.Explosion;
import me.termax.practice.lab08.entities.Player;

import java.awt.*;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;


public class GameState extends State {

    private Player player;
    private Explosion explosion;
    private Bullet bullet;
    private Set<Duck> ducks;

    private int duckSpawned;
    private int duckKilled;


    public GameState(Game game){
        super(game);
        player = new Player(game, game.width/2-Assets.player.getWidth()/2, game.height-Assets.player.getHeight()/2);
        this.ducks = ConcurrentHashMap.newKeySet();

        this.duckSpawned = 0;
        this.duckKilled = 0;
        Timer spawnNewDuck = new Timer();
        spawnNewDuck.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                ducks.removeIf(duck -> !duck.isVisible());
                int direction = game.getRandom().nextInt(2);
                int height = game.getRandom().nextInt(game.height-Assets.player.getHeight());
                if (direction == 0)
                    ducks.add(new Duck(game, 0, height, true));
                else
                    ducks.add(new Duck(game, game.width-Assets.duck.getWidth(), height, false));
                duckSpawned++;

            }
        }, 0, Settings.DUCK_SPAWN_RATE);
        Assets.playSound("ambience_loop", true);
    }

    @Override
    public void tick() {
        player.tick();
        if (explosion != null)
            explosion.tick();
        if (bullet != null)
            bullet.tick();
        for (Duck duck: ducks) {
            duck.tick();
            if (bullet != null && bullet.isVisible() && duck.isVisible())
                checkBulletKilledDuck(duck);
        }
    }

    private void renderBackground(Graphics g){
        g.drawImage(Assets.background, 0, 0, game.width, game.height, null);
        Font currentFont = g.getFont();
        g.setFont(currentFont.deriveFont(currentFont.getSize() * 2F));
        g.drawString("Ducks killed: " + duckKilled + "/" + duckSpawned, 5, game.getDisplay().getInsets().top);
    }

    @Override
    public void render(Graphics g) {
        renderBackground(g);
        if (explosion != null)
            explosion.render(g);
        if (bullet != null)
            bullet.render(g);
        player.render(g);
        for (Duck duck: ducks)
            duck.render(g);

    }

    private void checkBulletKilledDuck(Duck duck){
        float bulletX = bullet.getX()+bullet.getWidth()/2;
        float bulletY = bullet.getY();
        if (duck.getX() < bulletX && bulletX < duck.getX()+duck.getWidth() &&
                duck.getY() < bulletY && bulletY < duck.getY()+duck.getWidth()) {
            duckKilled++;
            bullet.setVisible(false);
            duck.setVisible(false);
            createExplosion(duck.getX(), duck.getY());
        }
    }

    public void createExplosion(float x, float y) {
        if ((explosion != null && !explosion.isVisible()) || explosion == null)
            explosion = new Explosion(x, y, true);
    }

    public void createBullet(float fromX, float fromY, float toX, float toY) {
        if ((bullet != null && !bullet.isVisible()) || bullet == null) {
            float distance = (float) Math.hypot(toX-fromX, toY-fromY);
            bullet = new Bullet(game,
                    fromX-Assets.bullet.getWidth()/2,
                    fromY-Assets.bullet.getHeight()/2,
                    (toX-fromX)*Settings.BULLET_SPEED/distance,
                    (toY-fromY)*Settings.BULLET_SPEED/distance,
                    (float)(Math.atan2(toY-fromY,toX-fromX) + Math.PI/2),
                    true);
        }
    }

}
