package novemberizing.document;

import novemberizing.html.Adjustor;
import novemberizing.html.model.Mark;
import org.jsoup.nodes.*;

import java.util.LinkedList;
import java.util.List;
import java.util.UUID;

public class NovemberizingHTMLAdjustor extends Adjustor {

    @Override
    public int length(Node node){
        if(node != null) {
            if(functional.string.equal(node.nodeName(), "blockquote")) {
                return 2;
            } else {
                return functional.string.contain(node.nodeName(), "p", "pre", "h1", "h2", "h3", "h4", "h5", "h6") ? 2 : super.length(node);
            }
        }
        return 0;
    }

    @Override
    public int length(String name){
        if(functional.string.equal(name, "blockquote")) {
            return 2;
        } else {
            return functional.string.contain(name, "p", "pre", "h1", "h2", "h3", "h4", "h5", "h6") ? 2 : super.length(name);
        }
    }

    @Override
    public Node end(Node node) {
        if(node != null) {
            if(functional.string.equal(node.nodeName(), "blockquote")) {
                return functional.list.end(node.childNodes());
            } else {
                return node;
            }
        }
        return null;
    }

    private int __end(Node node){
        if(node != null) {
            if(functional.string.equal(node.nodeName(), "blockquote")) {
                return 4;
            } else if(functional.string.contain(node.nodeName(), "p", "pre", "h1", "h2", "h3", "h4", "h5", "h6")) {
                return 2;
            }
        }
        return 0;
    }

    @Override
    public boolean end(Node node, int index) {
        return index + __end(node) == functional.html.length(node);
    }

    @Override
    public int index(Node node, int index){ return node != null && functional.string.equal(node.nodeName(), "blockquote") ? index - 1 : index; }

    @Override
    public Document document(Document o){
        if(o != null){
            Document.OutputSettings settings = o.outputSettings();
            settings.prettyPrint(false);
            settings.indentAmount(0);
            o.outputSettings(settings);
            LinkedList<Node> nodes = new LinkedList<>();
            for(Node node : functional.html.children(o.body())) {
                if(node instanceof TextNode) {
                    nodes.add(node);
                } else {
                    String id = node.attr("id");
                    if(functional.string.empty(id)) {
                        node.attr("id", functional.string.from(UUID.randomUUID()));
                    }
                    if(functional.html.is.list(node)) {
                        for(Node child : functional.html.children(node)) {
                            if(child instanceof TextNode) {
                                nodes.add(child);
                            } else if(functional.html.is.item(child)) {
                                for(Node _child : functional.html.children(child)) {
                                    if(_child instanceof TextNode) {
                                        nodes.add(_child);
                                    }
                                }
                            }
                        }
                    } else if(functional.html.is.blockquote(node)) {
                        for(Node child : functional.html.children(node)) {
                            if(child instanceof TextNode) {
                                nodes.add(child);
                            }
                        }
                    }
                }
            }
            for(Node node : nodes) {
                node.remove();
            }
        }
        return o;
    }

    @Override
    public List<Node> children(Mark mark, Element element) {
        if(mark != null && element != null) {
            if(functional.string.equal(mark.tag(), "blockquote")) {
                if(functional.string.equal(element.nodeName(), "blockquote")) {
                    return element.childNodesCopy();
                } else if(functional.string.contain(element.nodeName(), "p", "h1", "h2", "h3", "h4", "h5", "h6")) {
                    return functional.list.gen(element.clone());
                } else {
                    throw new RuntimeException("");
                }
            } else if(functional.string.equal(mark.tag(), "pre")) {
                if(functional.string.equal(element.nodeName(), "pre")) {
                    return element.childNodesCopy();
                } else if(functional.string.contain(element.nodeName(), "p", "h1", "h2", "h3", "h4", "h5", "h6")) {
                    List<Node> nodes = element.childNodesCopy();
                    if(nodes.size() == 0) {
                        return functional.list.gen(new Element("code"));
                    } else if(nodes.size() == 1) {
                        if(functional.html.is.text(nodes.get(0))) {
                            Element code = new Element("code");
                            code.appendChild(nodes.get(0));
                            return functional.list.gen(code);
                        } else {
                            throw new RuntimeException("");
                        }
                    } else {
                        throw new RuntimeException("");
                    }
                } else {
                    throw new RuntimeException("");
                }
            } else if(functional.string.contain(mark.tag(), "p", "h1", "h2", "h3", "h4", "h5", "h6")) {
                if(functional.string.contain(element.nodeName(), "p", "h1", "h2", "h3", "h4", "h5", "h6")) {
                    return element.childNodesCopy();
                } else if(functional.string.equal(element.nodeName(), "pre")) {
                    List<Node> children = element.childNodes();
                    if(functional.list.size(children) == 1) {
                        Node code = functional.list.begin(children);
                        if(functional.html.is.code(code)) {
                            return code.childNodesCopy();
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
        return null;
    }

    @Override
    public boolean block(Mark mark) {
        return mark != null && functional.string.contain(mark.tag(), "blockquote", "ol", "ul");
    }

    public NovemberizingHTMLAdjustor(){
        super("span");
    }
}
