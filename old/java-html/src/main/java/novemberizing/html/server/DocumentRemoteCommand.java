package novemberizing.html.server;

import com.google.gson.annotations.Expose;
import novemberizing.html.model.Mark;

import java.util.List;

public class DocumentRemoteCommand {
    public static DocumentRemoteCommand insert(String id, int from, String text, DocumentRemoteLine prev) {
        return new DocumentRemoteCommand("insert", id, from, text, prev);
    }

    public static DocumentRemoteCommand replace(String id, int from, int to, String text, DocumentRemoteLine prev) {
        return new DocumentRemoteCommand("replace", id, from, to, text, prev);
    }

    public static DocumentRemoteCommand replace(String id, int from, int to, Mark mark, DocumentRemoteLine prev) {
        return new DocumentRemoteCommand("replace", id, from, to, mark, prev);
    }

    public static DocumentRemoteCommand remove(String id, int from, int to, DocumentRemoteLine prev) {
        return new DocumentRemoteCommand("remove", id, from, to, prev);
    }

    public static DocumentRemoteCommand mark(String id, int from, int to, Mark mark, DocumentRemoteLine prev) {
        return new DocumentRemoteCommand("mark", id, from, to, mark, prev);
    }

    public static DocumentRemoteCommand unmark(String id, int from, int to, Mark mark, DocumentRemoteLine prev) {
        return new DocumentRemoteCommand("unmark", id, from, to, mark, prev);
    }

    public static DocumentRemoteCommand enter(String id, int from, int to, List<Mark> marks, DocumentRemoteLine prev) {
        return new DocumentRemoteCommand("enter", id, from, to, marks, prev);
    }

    public static DocumentRemoteCommand around(String id, int from, int to, Mark mark, DocumentRemoteLine prev) {
        return new DocumentRemoteCommand("around", id, from, to, mark, prev);
    }

    public static DocumentRemoteCommand unaround(String id, int from, int to, DocumentRemoteLine prev) {
        return new DocumentRemoteCommand("unaround", id, from, to, prev);
    }

    @Expose private String type;
    @Expose private int from;
    @Expose private int to;
    @Expose private String id;
    @Expose private DocumentRemoteLine prev;
    @Expose private String text;
    @Expose private List<Mark> marks;

    public String type(){ return type; }
    public int from(){ return from; }
    public int to(){ return to; }
    public String id(){ return id; }
    public DocumentRemoteLine prev(){ return prev; }
    public String text(){ return text; }
    public List<Mark> marks(){ return marks; }
    public Mark mark(){ return functional.list.begin(marks); }

    private DocumentRemoteCommand(String type, String id, int from, int to, String text, DocumentRemoteLine prev) {
        this.type = type;
        this.id = id;
        this.from = from;
        this.to = to;
        this.prev = prev;
        this.text = text;
        this.marks = null;
    }

    private DocumentRemoteCommand(String type, String id, int from, int to, DocumentRemoteLine prev) {
        this.type = type;
        this.id = id;
        this.from = from;
        this.to = to;
        this.prev = prev;
        this.text = "";
        this.marks = null;
    }

    private DocumentRemoteCommand(String type, String id, int from, String text, DocumentRemoteLine prev) {
        this.type = type;
        this.id = id;
        this.from = from;
        this.to = from;
        this.prev = prev;
        this.text = text;
        this.marks = null;
    }

    private DocumentRemoteCommand(String type, String id, int from, int to, Mark mark, DocumentRemoteLine prev) {
        this.type = type;
        this.id = id;
        this.from = from;
        this.to = to;
        this.prev = prev;
        this.text = "";
        this.marks = functional.list.gen(mark);
    }

    private DocumentRemoteCommand(String type, String id, int from, int to, List<Mark> marks, DocumentRemoteLine prev) {
        this.type = type;
        this.id = id;
        this.from = from;
        this.to = to;
        this.prev = prev;
        this.text = "";
        this.marks = marks;
    }

    private DocumentRemoteCommand(String type, String id, int from, int to) {
        this.type = type;
        this.id = id;
        this.from = from;
        this.to = to;
        this.prev = null;
        this.text = "";
        this.marks = null;
    }
}
