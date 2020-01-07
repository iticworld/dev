package hornet.editor.html.server;

import com.google.gson.annotations.Expose;
import hornet.editor.html.Line;
import hornet.editor.html.Mark;

import java.util.List;

public class RemoteDocumentCommand {
    @Expose protected String type;
    @Expose protected int from;
    @Expose protected int to;
    @Expose protected String id;
    @Expose protected Line prev;
    @Expose protected String text;
    @Expose protected List<Mark> marks;

    public String type(){ return type; }
    public int from(){ return from; }
    public int to(){ return to; }
    public String id(){ return id; }
    public Line prev(){ return prev; }
    public int index(){ return from; }
    public String text() {
        System.err.println("WHITE SPACE 가 올라오면 '_' 로 처리합니다. 무조건 수정해야 합니다.");
        return functional.string.exist(text) ? text.replace(" ", "_") : "";
    }
    public Mark mark(int index){ return functional.list.get(marks, index); }
    public List<Mark> marks(){ return marks; }

    public RemoteDocumentCommand(String type, String id, int index, List<Mark> marks, Line prev) {
        this.type = type;
        this.from = index;
        this.to = index;
        this.id = id;
        this.prev = prev;
        this.text = null;
        this.marks = marks;
    }

    public RemoteDocumentCommand(String type, String id, int from, int to, Mark mark) {
        this.type = type;
        this.from = from;
        this.to = to;
        this.id = id;
        this.prev = null;
        this.text = null;
        this.marks = functional.list.gen(mark);
    }

    public RemoteDocumentCommand(String type, String id, int from, int to, Mark mark, Line prev) {
        this.type = type;
        this.from = from;
        this.to = to;
        this.id = id;
        this.prev = prev;
        this.text = null;
        this.marks = functional.list.gen(mark);
    }

    public RemoteDocumentCommand(String type, String id, int from, int to, Line prev) {
        this.type = type;
        this.from = from;
        this.to = to;
        this.id = id;
        this.prev = prev;
        this.text = null;
    }

    public RemoteDocumentCommand(String type, String id, int from, int to) {
        this.type = type;
        this.from = from;
        this.to = to;
        this.id = id;
        this.prev = null;
        this.text = null;
    }

    public RemoteDocumentCommand(String type, String id, int from, int to, String text) {
        this.type = type;
        this.from = from;
        this.to = to;
        this.id = id;
        this.prev = null;
        this.text = text;
    }

    public RemoteDocumentCommand(String type, String id, int index, String text) {
        this.type = type;
        this.from = index;
        this.to = index;
        this.id = id;
        this.prev = null;
        this.text = text;
    }
}
