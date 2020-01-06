package hornet.editor.application.html;

import com.google.gson.annotations.Expose;
import hornet.editor.html.server.RemoteCoworker;

import javax.websocket.SendHandler;
import javax.websocket.Session;

public class NovemberizingRemoteCoworker extends RemoteCoworker {
    @Expose private String username;
    @Expose private String display;
    @Expose private String img;
    @Expose private String name;
    @Expose private String avatar;
    @Expose private String sessid;

    private String __key;
    private String __agent;
    private Session __session;

    public String username(){ return username; }
    public String sessid(){ return sessid; }

    @Override
    public <T> void send(T o, SendHandler result) {
        functional.ws.async(__session, o, result, "[broadcast:server > client]");
    }

    public NovemberizingRemoteCoworker(Session session, String username) {
        super(username);
        this.__session = session;
        this.sessid = username;
        this.username = username;
        this.display = username;
        this.name = username;
        this.avatar = "https://down.openur.biz/userProfile/-1";
        this.img = "https://down.openur.biz/userProfile/-1";
    }
}
