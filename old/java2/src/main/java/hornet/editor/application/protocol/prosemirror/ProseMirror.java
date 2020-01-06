package hornet.editor.application.protocol.prosemirror;

import com.google.gson.annotations.Expose;
import hornet.editor.html.Line;
import hornet.editor.html.attr.Style;
import hornet.editor.html.server.RemoteDocumentCommand;

import javax.validation.constraints.NotNull;
import java.util.List;

public class ProseMirror {
    public static RemoteDocumentCommand convert(Step step) {
        if(step != null && functional.string.exist(step.type())) {
            switch(step.type()) {
                case "replace": return __convert_replace_to_command(step);
                case "addMark": return __convert_mark_to_command(step);
                case "removeMark": return __convert_unmark_to_command(step);
                default: throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    private static hornet.editor.html.Mark convert(Content content) {
        if(content != null) {
            if(!functional.string.empty(content.type())) {
                switch(content.type()){
                    case "paragraph": return new hornet.editor.html.Mark("p", new hornet.editor.html.Attr("id", content.id()));
                    case "heading": return new hornet.editor.html.Mark("h" + content.level(), new hornet.editor.html.Attr("id", content.id()));
                    case "blockquote": return new hornet.editor.html.Mark("blockquote", new hornet.editor.html.Attr("id", content.id()));
                    case "ordered_list": return new hornet.editor.html.Mark("ol", new hornet.editor.html.Attr("id", content.id()));
                    case "bullet_list": return new hornet.editor.html.Mark("ul", new hornet.editor.html.Attr("id", content.id()));
                    case "code_block": return new hornet.editor.html.Mark("pre", new hornet.editor.html.Attr("id", content.id()));
                    default: throw new RuntimeException("");
                }
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    private static hornet.editor.html.Mark convert(Mark mark) {
        if(mark != null) {
            if(functional.string.exist(mark.type())) {
                switch(mark.type()) {
                    case "strong": return new hornet.editor.html.Mark("strong");
                    case "em": return new hornet.editor.html.Mark("em");
                    case "forecolor": return new hornet.editor.html.Mark(null, new Style("color", mark.color()));
                    case "bgcolor": return new hornet.editor.html.Mark(null, new Style("background-color", mark.color()));
                    case "underline": return new hornet.editor.html.Mark(null, new Style("text-decoration", "underline"));
                    case "del": return new hornet.editor.html.Mark(null, new Style("text-decoration", "line-through"));
                    default: throw new RuntimeException("");
                }
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    private static RemoteDocumentCommand __convert_mark_to_command(@NotNull Step step) {
        if(functional.string.exist(step.id())) {
            return new RemoteDocumentCommand("mark", step.id(), step.from(), step.to(), convert(step.mark()));
        } else {
            throw new RuntimeException("");
        }
    }

    private static RemoteDocumentCommand __convert_unmark_to_command(@NotNull Step step) {
        if(functional.string.exist(step.id())) {
            return new RemoteDocumentCommand("unmark", step.id(), step.from(), step.to(), convert(step.mark()));
        } else {
            throw new RuntimeException("");
        }
    }

    private static RemoteDocumentCommand __convert_replace_to_command(@NotNull Step step) {
        if(functional.string.exist(step.id())) {
            if(step.from() == step.to()) {
                if(functional.list.size(step.contents()) == 1) {
                    ProseMirror.Content content = step.content(0);
                    if(functional.string.equal(content.type(), "text")) {
                        if(functional.string.exist(content.text())) {
                            return new RemoteDocumentCommand("insert", step.id(), step.from(), content.text());
                        } else {
                            throw new RuntimeException("");
                        }
                    } else {
                        throw new RuntimeException("");
                    }
                } else if(functional.list.size(step.contents()) == 2) {
                    ProseMirror.Content first = step.content(0);
                    ProseMirror.Content second = step.content(1);
                    if(functional.string.contain(first.type(), "paragraph", "heading", "blockquote")) {
                        if(functional.string.contain(second.type(), "paragraph", "heading", "blockquote")) {
                            return new RemoteDocumentCommand("enter", step.id(), step.from(), functional.list.gen(convert(first), convert(second)), step.previous());
                        } else {
                            throw new RuntimeException("");
                        }
                    } else {
                        throw new RuntimeException("");
                    }
                } else {
                    throw new RuntimeException("");
                }
            } else if(step.from() < step.to()) {
                if(functional.list.empty(step.contents())) {
                    return new RemoteDocumentCommand("remove", step.id(), step.from(), step.to());
                } else if(functional.list.size(step.contents()) == 1) {
                    ProseMirror.Content content = step.content(0);
                    if(functional.string.equal(content.type(), "text")) {
                        if(functional.string.exist(content.text())) {
                            return new RemoteDocumentCommand("replace", step.id(), step.from(), step.to(), content.text());
                        } else {
                            throw new RuntimeException("");
                        }
                    } else if(functional.string.contain(content.type(), "paragraph")) {
                        return new RemoteDocumentCommand("exchange", step.id(), step.from(), step.to(), convert(step.content(0)), step.previous());
                        // throw new RuntimeException("");
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
    }


    public static class Previous extends Line {}

    public static class Attr {
        @Expose
        private String id;
        @Expose private String align;
        @Expose private String color;
        @Expose private Integer level;

        public String id(){ return id; }
        public String align(){ return align; }
        public String color(){ return color; }
        public Integer level(){ return level; }
    }

    public static class Content {
        @Expose private String type;
        @Expose private String text;
        @Expose private Attr attrs;

        public String type(){ return type; }
        public String text(){ return text; }
        public Attr attrs(){ return attrs; }
        public String id(){ return attrs != null ? attrs.id() : null; }
        public String align(){ return attrs != null ? attrs.align() : null; }
        public String color(){ return attrs != null ?  attrs.color() : null; }
        public Integer level(){ return attrs != null ? attrs.level() : null; }
    }

    public static class Mark {
        @Expose private String type;
        @Expose private Attr attrs;

        public String type(){ return type; }
        public Attr attr(){ return attrs; }
        public String id(){ return attrs != null ? attrs.id() : null; }
        public String color(){ return attrs != null ? attrs.color() : null; }
        public Integer level(){ return attrs != null ? attrs.level() : null; }
        public String align(){ return attrs != null ? attrs.align() : null; }
    }

    public static class Payload {
        @Expose private Long version;
        @Expose private String clientID;
        @Expose private List<Step> steps;

        public Long version(){ return version; }
        public String username(){ return clientID; }
        public Step step(int index){ return steps != null && 0 <= index && index < steps.size() ? steps.get(index) : null; }
        public List<Step> steps(){ return steps; }
    }

    public static class Slice {
        @Expose private Integer openStart;
        @Expose private Integer openEnd;
        @Expose private List<Content> content;

        public int start(){ return openStart; }
        public int end(){ return openEnd; }
        public List<Content> contents(){ return content; }
        public Content content(int i){ return content != null && 0<=i && i < content.size() ? content.get(i) : null; }
    }

    public static class Step {
        @Expose private String stepType;
        @Expose private Integer from;
        @Expose private Integer to;
        @Expose private String id;
        @Expose private Slice slice;
        @Expose private Previous previous;
        @Expose private Mark mark;

        public String type(){ return stepType; }
        public int from(){ return from - previous.start() - 1; }
        public int to(){ return to - previous.start() - 1; }
        public Slice slice(){ return slice; }
        public String id(){ return id; }
        public Previous previous(){ return previous; }
        public Mark mark(){ return mark; }

        public Content content(int i){ return slice != null ? slice.content(i) : null; }
        public List<Content> contents(){ return slice != null ? slice.contents() : null; }

    }
}