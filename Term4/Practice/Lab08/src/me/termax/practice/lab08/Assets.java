package me.termax.practice.lab08;

import javax.imageio.ImageIO;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import java.awt.image.BufferedImage;
import java.io.*;

public class Assets {

    public static BufferedImage background, player, duck, duck2, explosion, bullet;

    public static void init(){
        try {
            background = ImageIO.read(new File(Settings.RES_DIR+"/background.png"));
            player     = ImageIO.read(new File(Settings.RES_DIR+"/player.png"));
            duck       = ImageIO.read(new File(Settings.RES_DIR+"/duck.png"));
            duck2      = ImageIO.read(new File(Settings.RES_DIR+"/duck2.png"));
            explosion  = ImageIO.read(new File(Settings.RES_DIR+"/explosion.png"));
            bullet     = ImageIO.read(new File(Settings.RES_DIR+"/bullet.png"));

        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }

    public static synchronized void playSound(final String sound, boolean loop) {
        new Thread(() -> {
            try {
                Clip clip = AudioSystem.getClip();
                AudioInputStream inputStream = AudioSystem.getAudioInputStream(
                        new BufferedInputStream(
                                new FileInputStream(Settings.RES_DIR+"/sounds/"+sound+".wav")
                        ));
                clip.open(inputStream);
                if(loop)
                    clip.loop(Clip.LOOP_CONTINUOUSLY);
                clip.start();
            } catch (Exception e) {
                System.err.println(e.getMessage());
            }
        }).start();
    }

}

