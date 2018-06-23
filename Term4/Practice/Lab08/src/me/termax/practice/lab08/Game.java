package me.termax.practice.lab08;

import me.termax.practice.lab08.states.GameState;
import me.termax.practice.lab08.states.MenuState;
import me.termax.practice.lab08.states.State;

import java.awt.*;
import java.awt.image.BufferStrategy;
import java.util.Random;

public class Game implements Runnable {

    private static final int FPS = 60;

    private Display display;
    public int width, height;
    public String title;

    private boolean running = false;
    private Thread thread;

    private BufferStrategy bs;
    private Graphics g;
    private Point mousePosition;

    private Random random = new Random();

    //States
    private State currentState;
    private State gameState;
    private State menuState;

    //Input
    private InputManager inputManager;

    public Game(String title, int width, int height){
        this.width = width;
        this.height = height;
        this.title = title;
        inputManager = new InputManager();
    }

    private void init(){
        display = new Display(title, width, height);
        display.addKeyListener(inputManager);
        display.getCanvas().addMouseListener(inputManager);
        display.getCanvas().createBufferStrategy(3);
        Assets.init();
        mousePosition = new Point(width/2, height/2);

        gameState = new GameState(this);
        menuState = new MenuState(this);

        currentState = gameState;
    }

    private void tick(){
        if(currentState != null)
            currentState.tick();
    }

    private void render(){
        bs = display.getCanvas().getBufferStrategy();
        g = bs.getDrawGraphics();
        g.clearRect(0, 0, width, height);

        if(currentState != null)
            currentState.render(g);

        bs.show();
        g.dispose();
    }

    public void run(){
        init();
        double timePerTick = 1000000000 / FPS;
        double delta = 0;
        long now;
        long lastTime = System.nanoTime();

        while(running){
            now = System.nanoTime();
            delta += (now - lastTime) / timePerTick;
            lastTime = now;
            if(delta >= 1){
                tick();
                render();
                delta--;
            }
        }
        stop();
    }

    public InputManager getInputManager(){
        return inputManager;
    }

    public Point getMousePosition(){
        Point newMousePosition = getDisplay().getMousePosition();
        if (newMousePosition != null) {
            mousePosition = newMousePosition;
            mousePosition.setLocation(mousePosition.getX(), mousePosition.getY()-getDisplay().getInsets().top);
        }
        return mousePosition;
    }

    public synchronized void start(){
        if(running)
            return;
        running = true;
        thread = new Thread(this);
        thread.start();
    }

    public synchronized void stop(){
        if(!running)
            return;
        running = false;
        try {
            thread.join();
        } catch (InterruptedException e) {
            System.exit(-1);
        }
    }

    public Display getDisplay() {
        return display;
    }

    public State getCurrentState() {
        return currentState;
    }

    public Random getRandom() {
        return random;
    }
}
