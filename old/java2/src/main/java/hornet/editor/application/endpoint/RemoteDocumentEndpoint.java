package hornet.editor.application.endpoint;

import com.google.gson.JsonSyntaxException;
import hornet.editor.application.html.NovemberizingRemoteCoworker;
import hornet.editor.application.html.NovemberizingRemoteDocument;
import hornet.editor.application.protocol.RemoteDocumentPacketType;
import hornet.editor.application.protocol.broadcast.BroadcastCoworkerList;
import hornet.editor.application.protocol.broadcast.BroadcastDocumentUpdate;
import hornet.editor.application.protocol.prosemirror.ProseMirror;
import hornet.editor.application.protocol.request.ChangePosReq;
import hornet.editor.application.protocol.request.DocumentGetReq;
import hornet.editor.application.protocol.request.UpdateDocumentReq;
import hornet.editor.application.protocol.response.ChangePosRes;
import hornet.editor.application.protocol.response.DocumentGetRes;
import hornet.editor.application.protocol.response.UpdateDocumentRes;
import hornet.editor.html.server.RemoteCoworker;
import hornet.editor.html.server.RemoteDocument;
import hornet.editor.html.server.RemoteDocumentCommand;
import hornet.editor.html.server.RemoteDocumentMap;
import novemberizing.Packet;

import javax.websocket.*;
import javax.websocket.server.ServerEndpoint;
import java.io.IOException;
import java.util.List;

@ServerEndpoint("/api/collab/doc/{id}")
public class RemoteDocumentEndpoint {
    private static RemoteDocumentMap __documents = RemoteDocumentMap.get();

    private String __id = null;
    private String __username = null;
    private RemoteDocument __document;
    private NovemberizingRemoteCoworker __me;

    private void result(SendResult result){

    }

    @OnOpen
    public void onOpen(Session session) {
        __id = functional.ws.path.get(session, "id");
        __username = functional.ws.request.get(session, "username");
        if(!functional.string.empty(__username)) {
            __document = __documents.load(__id, NovemberizingRemoteDocument::new, __id);
            List<RemoteCoworker> coworkers = __document.join(__me = new NovemberizingRemoteCoworker(session, __username));
            __document.load();
            __document.broadcast(new BroadcastCoworkerList(coworkers), this::result);
        } else {
            System.out.println("not found username");
            try {
                session.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void onDocumentLoadReq(Session session, DocumentGetReq req) {
        __document.get((document) -> functional.ws.async(session, new DocumentGetRes(req, document), this::result, "[single:server > client]"));
        __document.broadcast(new BroadcastCoworkerList(__document.users()), this::result);
    }

    private void onChangePosReq(Session session, ChangePosReq req) {
        List<String> prev = __me.pos();
        List<String> next = __document.own(__me, prev, req.pos());
        __me.pos(next);
        List<RemoteCoworker> users = __document.users();
        functional.ws.async(session, new ChangePosRes(req, users), this::result, "[single:server > client]");
        __document.broadcast(new BroadcastCoworkerList(__document.users()), this::result);
    }

    private void onDocumentUpdate(Session session, UpdateDocumentReq req) {
        ProseMirror.Payload payload = req.payload();
        if(payload == null || functional.list.empty(payload.steps())) {
            throw new RuntimeException("invalid parameter exception");
        }
        Long version = null;
        try {
            __document.lock();
            Long v = null;
            for(ProseMirror.Step step : payload.steps()) {
                try {
                    v = __document.exec(ProseMirror.convert(step));
                } catch(Exception e) {
                    e.printStackTrace();
                }
            }
            version = v;
        } catch(Exception e) {
            e.printStackTrace();
        } finally {
            __document.unlock();
        }
        if(version != null) {
            functional.ws.async(session, UpdateDocumentRes.ok(req, version), this::result, "[single:server > client]");
            __document.broadcast(new BroadcastDocumentUpdate(__me.username(), __me.sessid(), version, payload.steps()), this::result);
        } else {
            functional.ws.async(session, UpdateDocumentRes.fail(req, version), this::result, "[single:server > client]");
        }
    }

    @OnMessage
    public void onMessage(Session session, String message) {
        System.out.println("[client > server] " + message);
        Packet packet = functional.json.from(message, Packet.class);
        if(packet != null && functional.string.exist(packet.type())) {
            switch(packet.type()) {
                case RemoteDocumentPacketType.GET: onDocumentLoadReq(session, functional.json.from(message, DocumentGetReq.class)); break;
                case RemoteDocumentPacketType.CHANGEPOS: onChangePosReq(session, functional.json.from(message, ChangePosReq.class)); break;
                case RemoteDocumentPacketType.UPDATE: onDocumentUpdate(session, functional.json.from(message, UpdateDocumentReq.class)); break;
                default: throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    @OnError
    public void onError(Session session, Throwable e) {
        System.out.println("error");
        e.printStackTrace();
    }

    @OnClose
    public void onClose(Session session) {
        System.out.println("close");
    }
}
