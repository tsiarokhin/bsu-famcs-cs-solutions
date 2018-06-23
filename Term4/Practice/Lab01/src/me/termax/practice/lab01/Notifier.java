package me.termax.practice.lab01;

import java.util.Set;

public class Notifier<T extends Notifiable> {
    protected Set<T> notifiables;

    public Notifier(Set<T> notifiables) {
        this.notifiables = notifiables;
    }

    public void doNotifyAll(String message) {
        for (Notifiable nt : notifiables) {
            nt.notify(message);
        }
    }
}
