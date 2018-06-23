package me.termax.practice.lab08;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class InputManager implements KeyListener, MouseListener {

    private boolean isLeft, isRight, isShoot;

    public InputManager(){
        isLeft = isRight = isShoot = false;
    }

    private void newKeyState(KeyEvent e, boolean isPressed) {
        switch (e.getKeyCode()) {
            case KeyEvent.VK_A:
                isLeft = isPressed;
                break;
            case KeyEvent.VK_D:
                isRight = isPressed;
                break;
            case KeyEvent.VK_SPACE:
                isShoot = isPressed;
                break;
        }
    }

    @Override
    public void keyPressed(KeyEvent e) {
        newKeyState(e, true);
    }

    @Override
    public void keyReleased(KeyEvent e) {
        newKeyState(e, false);
    }

    @Override
    public void mousePressed(MouseEvent e) {
        if (e.getButton() == MouseEvent.BUTTON1)
            isShoot = true;
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        if (e.getButton() == MouseEvent.BUTTON1)
            isShoot = false;
    }

    public boolean isLeft() {
        return isLeft;
    }

    public boolean isRight() {
        return isRight;
    }

    public boolean isShoot() {
        return isShoot;
    }

    @Override
    public void keyTyped(KeyEvent e) { }
    @Override
    public void mouseClicked(MouseEvent e) { }
    @Override
    public void mouseEntered(MouseEvent e) { }
    @Override
    public void mouseExited(MouseEvent e) { }
}
