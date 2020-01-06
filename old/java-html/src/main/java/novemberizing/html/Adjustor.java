package novemberizing.html;

import novemberizing.html.model.Mark;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.nodes.Node;

import java.util.List;

public class Adjustor {
    protected static final String DEFAULT_TAG = "span";

    protected String tag = DEFAULT_TAG;

    public String tag(){ return tag; }
    public int length(Node node){ return 0; }
    public int length(String name){ return 0; }
    public int index(Node node, int index){ return index; }
    public Node end(Node node){ return node; }

    public Document document(Document o){ return o; }

    public boolean end(Node node, int index) {
        return index == functional.html.length(node);
    }

    public List<Node> children(Mark mark, Element element) {
        if(mark != null && element != null) {
            return element.childNodesCopy();
        }
        return null;
    }

    public boolean block(Mark mark) { return mark != null && functional.html.is.appendable(mark); }

    public Adjustor(){
        this.tag = DEFAULT_TAG;
    }

    public Adjustor(String tag) {
        this.tag = tag;
    }
}
