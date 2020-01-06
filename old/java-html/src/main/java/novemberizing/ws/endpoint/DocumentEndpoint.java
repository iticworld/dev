package novemberizing.ws.endpoint;

import com.google.gson.JsonSyntaxException;
import novemberizing.document.NovemberizingDocumentRemoteCoworker;
import novemberizing.document.NovemberizingDocumentRemoteRoot;
import novemberizing.document.NovemberizingDocumentServerPacketType;
import novemberizing.html.model.Attr;
import novemberizing.html.model.Mark;
import novemberizing.html.model.attr.Style;
import novemberizing.html.server.DocumentRemoteCommand;
import novemberizing.html.server.DocumentRemoteCoworker;
import novemberizing.html.server.DocumentRemoteRoot;
import novemberizing.html.server.DocumentRemoteRootMap;
import novemberizing.packet.Packet;
import novemberizing.ws.protocol.broadcast.BroadcastUpdatePacket;
import novemberizing.ws.protocol.broadcast.BroadcastUserPacket;
import novemberizing.ws.protocol.prosemirror.ProseMirror;
import novemberizing.ws.protocol.request.ChangePosReq;
import novemberizing.ws.protocol.request.DocumentServerInitReq;
import novemberizing.ws.protocol.request.DocumentUpdateReq;
import novemberizing.ws.protocol.response.ChangePosRes;
import novemberizing.ws.protocol.response.DocumentServerInitRes;
import novemberizing.ws.protocol.response.DocumentUpdateRes;

import javax.websocket.*;
import javax.websocket.server.ServerEndpoint;
import java.io.IOException;
import java.util.List;

@ServerEndpoint("/api/collab/doc/{id}")
public class DocumentEndpoint {
    private static DocumentRemoteRootMap __documents = DocumentRemoteRootMap.get();

    private String __id = null;
    private String __username = null;
    private DocumentRemoteRoot __document;
    private NovemberizingDocumentRemoteCoworker __me;

    @OnOpen
    public void onOpen(Session session) {
        __id = functional.ws.path.get(session, "id");
        __username = functional.ws.request.get(session, "username");
        if(!functional.string.empty(__username)) {
            __document = __documents.load(__id, NovemberizingDocumentRemoteRoot::new, __id);
            List<DocumentRemoteCoworker> coworkers = __document.join(__me = new NovemberizingDocumentRemoteCoworker(session, __username));
            __document.load();
            // __document.broadcast(new BroadcastUserPacket(coworkers), this::result);
        } else {
            System.out.println("not found username");
            try {
                session.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void result(SendResult result){

    }

    private void onDocumentServerInit(Session session, DocumentServerInitReq req) {
        __document.get((document) -> functional.ws.async(session, new DocumentServerInitRes(req, document), this::result));
        __document.broadcast(new BroadcastUserPacket(__document.users()), this::result);
    }

    private void onChangePos(Session session, ChangePosReq req) {
        List<String> prev = __me.pos();
        List<String> next = __document.own(__me, prev, req.pos());
        __me.pos(next);
        List<DocumentRemoteCoworker> users = __document.users();
        functional.ws.async(session, new ChangePosRes(req, users), this::result);
        __document.broadcast(new BroadcastUserPacket(__document.users()), this::result);
    }

    private Mark convert(ProseMirror.Content content) {
        if(content != null) {
            if(!functional.string.empty(content.type())) {
                switch(content.type()){
                    case "paragraph": return new Mark("p", new Attr("id", content.id()));
                    case "heading": return new Mark("h" + content.level(), new Attr("id", content.id()));
                    case "blockquote": return new Mark("blockquote", new Attr("id", content.id()));
                    case "ordered_list": return new Mark("ol", new Attr("id", content.id()));
                    case "bullet_list": return new Mark("ul", new Attr("id", content.id()));
                    case "code_block": return new Mark("pre", new Attr("id", content.id()));
                    default: throw new RuntimeException("");
                }
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    private Mark convert(ProseMirror.Mark mark) {
        if(mark != null) {
            if(!functional.string.empty(mark.type())) {
                switch(mark.type()) {
                    case "strong": return new Mark("strong");
                    case "em": return new Mark("em");
                    case "forecolor": return new Mark("span", new Style("color", mark.color()));
                    case "bgcolor": return new Mark("span", new Style("background-color", mark.color()));
                    case "underline": return new Mark("span", new Style("text-decoration", "underline"));
                    case "del": return new Mark("span", new Style("text-decoration", "line-through"));
                    default: throw new RuntimeException("");
                }
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    private DocumentRemoteCommand gen(String type, ProseMirror.Step step) {
        if(functional.string.equal(type, "replace")) {
            if(step.from() <= step.to()) {
                List<ProseMirror.Content> contents = step.contents();
                if(functional.list.size(contents) == 1) {
                    ProseMirror.Content content = contents.get(0);
                    if(functional.string.equal(content.type(), "text")) {
                        if(!functional.string.empty(content.text())) {
                            if(step.from() == step.to()) {
                                return DocumentRemoteCommand.insert(step.id(), step.from(), content.text(), step.previous());
                            } else {
                                return DocumentRemoteCommand.replace(step.id(), step.from(), step.to(), content.text(), step.previous());
                            }
                        } else {
                            if(step.from() != step.to()) {
                                return DocumentRemoteCommand.remove(step.id(), step.from(), step.to(), step.previous());
                            } else {
                                throw new RuntimeException("");
                            }
                        }
                    } else if(functional.string.equal(content.type(), "paragraph")){
                        return DocumentRemoteCommand.replace(step.id(), step.from(), step.to(), convert(content), step.previous());
                    } else {
                        throw new RuntimeException("");
                    }
                } else if(functional.list.size(contents) == 0) {
                    if(step.from() < step.to()) {
                        return DocumentRemoteCommand.remove(step.id(), step.from(), step.to(), step.previous());
                    } else {
                        throw new RuntimeException("");
                    }
                } else if(functional.list.size(contents) == 2) {
                    ProseMirror.Content front = contents.get(0);
                    ProseMirror.Content end = contents.get(1);
                    if(functional.string.contain(front.type(), "paragraph", "heading", "blockquote")) {
                        System.out.println(end.type());
                        if(functional.string.contain(end.type(), "paragraph", "heading", "blockquote")) {
                            return DocumentRemoteCommand.enter(step.id(), step.from(), step.to(), functional.list.gen(convert(front), convert(end)), step.previous());
                        } else {
                            throw new RuntimeException("");
                        }
                    } else {
                        throw new RuntimeException("");
                    }
                } else {
                    throw new RuntimeException("");
                }
            } else {
                throw new RuntimeException("");
            }
        } else if(functional.string.equal(type, "addMark")) {
            return DocumentRemoteCommand.mark(step.id(), step.from(), step.to(), convert(step.mark()), step.previous());
        } else if(functional.string.equal(type, "removeMark")) {
            return DocumentRemoteCommand.unmark(step.id(), step.from(), step.to(), convert(step.mark()), step.previous());
        } else if(functional.string.equal(type, "replaceAround")) {
            System.out.println(functional.json.from(step));
            if(functional.list.size(step.contents()) == 1) {
                return DocumentRemoteCommand.around(step.id(), step.from(), step.to(), convert(step.content(0)), step.previous());
            } else if(functional.list.size(step.contents()) == 0) {
                return DocumentRemoteCommand.unaround(step.id(), step.from(), step.to(), step.previous());
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    private DocumentRemoteCommand gen(ProseMirror.Step step) {
        if(step.type() != null) {
            switch(step.type()) {
                case "replace": return gen(step.type(), step);
                case "addMark": return gen(step.type(), step);
                case "removeMark": return gen(step.type(), step);
                case "replaceAround": return gen(step.type(), step);
                default: throw new RuntimeException(""); // ordered_list, bullet_list
            }
        }
        throw new RuntimeException("");
    }

    private void onDocumentUpdate(Session session, DocumentUpdateReq req) {
        System.out.println(functional.json.from(req));
        ProseMirror.Payload payload = req.payload();
        if(payload == null || functional.list.empty(payload.steps())) {
            throw new RuntimeException("invalid parameter exception");
        }
        Long version = null;
        try {
            __document.lock();
            Long v = null;
            for(ProseMirror.Step step : payload.steps()) {
                v = __document.exec(gen(step));
            }
            version = v;
        } catch(Exception e) {
            e.printStackTrace();
            System.err.println("how to this");
        } finally {
            __document.unlock();
        }
        if(version != null) {
            functional.ws.async(session, DocumentUpdateRes.ok(req, version), this::result);
            __document.broadcast(new BroadcastUpdatePacket(__me.username(), __me.sessid(), version, payload.steps()), this::result);
        } else {
            functional.ws.async(session, DocumentUpdateRes.fail(req, version), this::result);
        }
    }

    @OnMessage
    public void onMessage(Session session, String message) {
        System.out.println(message);
        try {
            Packet packet = functional.json.to(message, Packet.class);
            switch(functional.ws.packet.type(packet)) {
                case NovemberizingDocumentServerPacketType.INIT: onDocumentServerInit(session, functional.json.to(message, DocumentServerInitReq.class)); break;
                case NovemberizingDocumentServerPacketType.CHANGEPOS: onChangePos(session, functional.json.to(message, ChangePosReq.class)); break;
                case NovemberizingDocumentServerPacketType.UPDATE: onDocumentUpdate(session, functional.json.to(message, DocumentUpdateReq.class)); break;
                default: throw new RuntimeException("");
            }
        } catch(JsonSyntaxException e) {
            System.out.println("message: " + message);
            throw e;
        }
    }

    @OnError
    public void onError(Session session, Throwable exception) {
        System.out.println("error");
        exception.printStackTrace();
        try {
            session.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @OnClose
    public void onClose(Session session) {
        System.out.println("close");
        if(__me != null && __document != null) {
            List<DocumentRemoteCoworker> coworkers = __document.leave(__me);
            if(coworkers != null) {
                __document.broadcast(new BroadcastUserPacket(coworkers), this::result);
            }
        }
        __me = null;
        __document = null;
    }
}
