package novemberizing.dom;

import com.google.gson.annotations.Expose;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Node {
    protected Node parent;
    @Expose protected List<Node> children;
    @Expose protected String name;
    @Expose protected String value;
    @Expose protected Map<String, String> attrs;

    public Node parent(){ return parent; }
    public Node child(int index){ return functional.list.get(children, index); }
    public List<Node> children(){ return children; }
    public String name(){ return name; }
    public String value(){ return value; }
    public Map<String, String> attrs(){ return attrs; }
    public String attr(String name){ return functional.map.get(attrs, name); }

    public void value(String v){ value = v; }

    public void add(Node child){
        if(children == null) {
            children = new ArrayList<>();
        }
        children.add(child);
    }

    protected Node(String name) {
        this.name = name;
        this.parent = null;
        this.children = null;
        this.value = null;
        this.attrs = null;
    }

    public Node(Node parent, Spec spec) {
        this.name = spec.name();
        this.parent = parent;
        this.children = null;
        this.value = null;
        this.attrs = null;
    }

    public Node(Node parent, String name) {
        this.name = name;
        this.parent = parent;
        this.children = null;
        this.value = null;
        this.attrs = null;
    }

    public Node(Node parent, String name, String value) {
        this.name = name;
        this.parent = parent;
        this.children = null;
        this.value = value;
        this.attrs = null;
    }

    public Node(Node parent, String name, String value, Map<String, String> attrs) {
        this.name = name;
        this.parent = parent;
        this.children = null;
        this.value = value;
        this.attrs = attrs;
    }

    public Node(Node parent, String name, Map<String, String> attrs) {
        this.name = name;
        this.parent = parent;
        this.children = null;
        this.value = null;
        this.attrs = attrs;
    }
}
