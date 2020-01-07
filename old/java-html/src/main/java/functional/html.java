package functional;

import novemberizing.html.Adjustor;
import novemberizing.html.Visitor;
import novemberizing.html.model.Attr;
import novemberizing.html.model.Mark;

import novemberizing.html.server.DocumentRemoteLine;
import novemberizing.tuple.Triple;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.nodes.Node;
import org.jsoup.nodes.TextNode;

import java.io.IOException;
import java.net.URL;
import java.util.*;

public class html {
    private static Adjustor __adjustor = null;
    public static class validate {
        public static boolean tag(String v){ return !functional.string.empty(v); }
    }

    public static class adjust {
        public static int length(String tag) {
            if(__adjustor != null) {
                return __adjustor.length(tag);
            }
            return 0;
        }
        public static String tag(String v){
            if(!functional.html.validate.tag(v)) {
                if(__adjustor != null) {
                    return __adjustor.tag();
                }
            }
            return v;
        }

        public static Node end(Node node) { return __adjustor != null ? __adjustor.end(node) : node; }

        public static Triple<Element, Integer, Integer> find(Element element, int index) {
            if(element != null) {
                List<Element> nodes = element.children();
                int total = 0;
                for(Element node : nodes) {
                    int length = functional.html.length(node);
                    if(total <= index && index < total + length) {
                        return new Triple<>(node, total, total + length);
                    }
                    total += length;
                }
            }
            return null;
        }
    }

    public static class to {
        public static Document document(String v) {
            v = functional.string.get(v);
            v = v.replaceAll(">\\s+", ">");
            v = v.replaceAll("\\s+<", "<");
            Document document = Jsoup.parse(functional.string.get(v));
            return __adjustor != null ? __adjustor.document(document) : document;
        }

        public static Document document(URL v) {
            try {
                Document document = Jsoup.parse(v, 5000);
                return __adjustor != null ? __adjustor.document(document) : document;
            } catch (IOException e) {
                e.printStackTrace();
                throw new RuntimeException("");
            }
        }

        public static Element body(String v) {
            Document document = functional.html.to.document(v);
            return document.body();
        }

        public static List<Element> elements(String v) {
            Document document = functional.html.to.document(v);
            Element body = document.body();
            return body.children();
        }

        public static List<Node> nodes(String v) {
            Document document = functional.html.to.document(v);
            Element body = document.body();
            return body.childNodes();
        }

        public static Element element(Mark mark) {
            if(mark == null) {
                throw new RuntimeException("invalid parameter exception");
            }
            String tag = functional.html.adjust.tag(mark.tag());
            if(!functional.html.validate.tag(tag)) {
                throw new RuntimeException("invalid parameter exception");
            }
            Element element = new Element(tag);
            Collection<Attr> collection = mark.attrs();
            if(functional.collection.exist(collection)) {
                for(Attr attr : collection) {
                    if(attr != null) {
                        element.attr(attr.name(), attr.value());
                    }
                }
            }
            return element;
        }

        public static Element element(Mark mark, Node node) {
            Element element = functional.html.to.element(mark);
            if(node != null) {
                element.appendChild(node);
            } else {
                System.err.println("node == null");
            }
            return element;
        }

        public static Element element(Mark mark, List<? extends Node> nodes) {
            return functional.html.to.element(mark, nodes, false);
        }

        public static Element element(Mark mark, List<? extends Node> nodes, boolean clone) {
            Element element = functional.html.to.element(mark);
            if(functional.list.exist(nodes)) {
                ArrayList<Node> children = new ArrayList<>(nodes);
                for(Node child : children) {
                    if(child != null) {
                        element.appendChild(child.clone());
                    } else {
                        System.err.println("child is null");
                    }
                }
            } else {
                System.err.println("nodes is empty");
            }
            return element;
        }

        public static String code(TextNode node) {
            if(node != null) {
                return node.outerHtml();
            }
            return "";
        }

        public static String text(TextNode node, boolean code) {
            if(node != null) {
                String s = node.getWholeText();
                if(!code) {
                    s = s.replaceAll("\n","");
                    s = functional.html.to.text(s, false);
                }
                return s;
            }
            return "";
        }

        public static String text(String v, boolean code) {
            if(v != null) {
                if(code) {
                    System.out.println("why");
                    return v;
                }
                String s = v.replaceAll("\n","");
                s = s.replace("&nbsp;", "\u00A0");
                s = s.replace(" ", "\u00A0");
                s = s.replace("&lt;", ">");
                s = s.replace("&gt;", "<");
                s = s.replace("&amp;", "&");
                return s;
            }
            return "";
        }

        public static String text(Node node, boolean code) {
            StringBuilder builder = new StringBuilder();
            if(node != null) {
                functional.html.traverse(node, (start, end, depth, n) -> {
                    if(n instanceof TextNode) {
                        builder.append(functional.html.to.text((TextNode) n, code));
                    } else if(functional.html.is.br(n)) {
                        throw new RuntimeException("");
                        // builder.append(" ");
                    }
                    return true;
                });
            }
            return builder.toString();
        }

        public static String html(Element element, boolean inner) {
            if(element != null) {
                return (inner ? element.html() : element.outerHtml());
            }
            return "";
        }

        public static String html(Node node) { return node != null ? node.outerHtml() : ""; }

        public static String html(List<? extends Node> nodes) {
            StringBuilder builder = new StringBuilder();
            if(functional.list.exist(nodes)) {
                for(Node node : nodes) {
                    if(node != null) {
                        builder.append(node.outerHtml());
                    }
                }
            }
            return builder.toString();
        }
    }

    public static class is {
        public static boolean code(Node node){ return node != null && functional.string.equal("code", node.nodeName()); }
        public static boolean item(Node node) { return node != null && functional.string.equal("li", node.nodeName()); }

        public static boolean pre(Node node){ return node != null && functional.string.equal("pre", node.nodeName()); }
        public static boolean list(Node node){ return node != null && functional.string.equal("ul", node.nodeName()); }
        public static boolean order(Node node){ return node != null && functional.string.equal("order", node.nodeName()); }
        public static boolean blockquote(Node node) { return node != null && functional.string.equal("blockquote", node.nodeName()); }

        public static boolean pre(Mark mark){ return mark != null && functional.string.equal("pre", mark.tag()); }
        public static boolean list(Mark mark){ return mark != null && functional.string.equal("ul", mark.tag()); }
        public static boolean order(Mark mark){ return mark != null && functional.string.equal("order", mark.tag()); }
        public static boolean blockquote(Mark mark) { return mark != null && functional.string.equal("blockquote", mark.tag()); }

        public static boolean br(Node node) { return node != null && functional.string.equal("br", node.nodeName()); }
        public static boolean br(Mark mark) { return mark != null && functional.string.equal("br", mark.tag()); }
        public static boolean leaf(Node node){ return !functional.html.has.children(node); }
        public static boolean element(Node node){ return node instanceof Element; }

        public static boolean text(Node node){ return node instanceof TextNode; }
        public static boolean text(Mark mark){ return mark != null && functional.string.equal(mark.tag(), "text"); }

        public static boolean appendable(Node node){ return !functional.html.is.text(node) && !functional.html.is.br(node); }
        public static boolean appendable(Mark mark){ return !functional.html.is.text(mark) && !functional.html.is.br(mark); }

        public static boolean block(Node node){ return node != null && functional.string.contain(node.nodeName(), "blockquote", "ol", "ul"); }
        public static boolean block(Mark mark) {
            return __adjustor != null ? __adjustor.block(mark) : functional.html.is.appendable(mark);
        }

        public static boolean end(Node node, int index) {
            if(node != null) {
                if(__adjustor != null) {
                    return __adjustor.end(node, index);
                } else {
                    return index == functional.html.length(node);
                }
            } else if(index > 0 || index < 0) {
                throw new RuntimeException("");
            }
            return true;
        }
    }

    public static class has {
        public static boolean children(Node node){ return node != null && node.childNodeSize() > 0; }
        public static boolean next(Node node){ return node != null && node.nextSibling() != null; }
        public static boolean prev(Node node){ return node != null && node.previousSibling() != null; }
        public static boolean parent(Node node){ return node != null && node.parent() != null; }
        public static boolean parent(Node node, String tag) {
            while(node != null && node.parent() != null) {
                if(functional.string.equal(node.nodeName(), tag)) {
                    return true;
                }
                node = node.parent();
            }
            return false;
        }
        public static boolean parent(Node node, String tag, String... tags) {
            while(node != null && node.parent() != null) {
                if(functional.string.equal(node.nodeName(), tag)) {
                    return true;
                }
                if(tag != null) {
                    for(String s : tags) {
                        if(functional.string.equal(node.nodeName(), s)) {
                            return true;
                        }
                    }
                }
                node = node.parent();
            }
            return false;
        }
    }

    public static void init(Adjustor adjustor){ __adjustor = adjustor; }

    public static Element get(Document document, String id, DocumentRemoteLine line) {
        if(document != null) {
            if(!functional.string.empty(id)) {
                Element element = document.getElementById(id);
                if(element == null) {
                    if(line != null) {
                        if(!functional.string.empty(line.id())) {
                            element = document.getElementById(line.id());
                            element = element.nextElementSibling();
                        } else {
                            element = document.child(0);
                        }
                    } else {
                        throw new RuntimeException("");
                    }
                }
                return element;
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static void print(List<Node> nodes) {
        if(nodes != null) {
            for(int i = 0; i < nodes.size(); i++) {
                System.out.println(String.format(Locale.getDefault(), "[%d] %s", i, nodes.get(0)));
            }
        }
    }

    public static String id(Element element){ return element != null ? element.id() : null; }

    public static String name(Node node){ return node != null ? node.nodeName() : ""; }

    public static boolean equal(Node node, Attr attr) {
        if(node != null && attr != null) {
            String v = node.attr(attr.name());
            return functional.string.equal(v, attr.value());
        }
        throw new RuntimeException("");
    }

    public static boolean equal(Node node, Collection<Attr> attrs) {
        if(node != null && attrs != null) {
            for(Attr attr : attrs) {
                if(attr != null) {
                    if(!functional.html.equal(node, attr)) {
                        return false;
                    }
                }
            }
            return true;
        }
        throw new RuntimeException("");
    }

    public static boolean equal(Node node, Mark mark) {
        if(node != null) {
            if(functional.html.validate.tag(mark.tag())) {
                if(functional.string.equal(mark.tag(), node.nodeName())) {
                    return mark.attrs() == null || functional.html.equal(node, mark.attrs());
                }
            } else {
                return  mark.attrs() != null && functional.html.equal(node, mark.attrs());
            }
            return false;
        }
        throw new RuntimeException("");
    }

    public static Node begin(List<Node> nodes) { return functional.list.begin(nodes); }
    public static Node end(List<Node> nodes) { return functional.list.end(nodes); }

    public static Node parent(Node node){ return node != null ? node.parent() : null; }
    public static List<Node> children(Node node){ return node != null ? node.childNodes() : null; }
    public static List<Node> children(Node node, boolean clone) {
        if(node != null) {
            return clone ? node.childNodesCopy() : node.childNodes();
        }
        return null;
    }

    public static List<Node> children(Mark mark, Element element) {
        if(mark != null && element != null) {
            if(__adjustor != null) {
                return __adjustor.children(mark, element);
            } else {
                return element.childNodesCopy();
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static int distance(Node parent, Node child) {
        if(parent == null || child == null) {
            throw new RuntimeException("invalid parameter exception");
        }
        int total = 0;
        List<Node> children = parent.childNodes();
        for(Node node : children) {
            if(node != child) {
                total += functional.html.length(node);
                continue;
            }
            return total;
        }
        throw new RuntimeException("invalid parameter exception");
    }

    public static int index(Node node, int index) { return __adjustor != null ? __adjustor.index(node, index) : index; }

    public static int length(Node node, Node until) {
        int total = 0;
        if(node != null) {
            do {
                if(functional.html.is.leaf(node)) {
                    if(node instanceof TextNode) {
                        String s = functional.html.to.text((TextNode) node, functional.html.is.pre(node.parent()));
                        total += s.length();
                    } else if(functional.html.is.br(node)) {
                        total += 1;
                    } else if(__adjustor != null) {
                        total += __adjustor.length(node);
                    }
                } else if(__adjustor != null) {
                    total += __adjustor.length(node);
                }
                if(functional.html.has.children(node)) {
                    node = functional.html.begin(node.childNodes());
                } else if(functional.html.has.next(node)) {
                    if(node != until) {
                        node = node.nextSibling();
                    }
                } else {
                    while(node != null && node != until) {
                        node = node.parent();
                        if(node != null && node != until && node.nextSibling() != null) {
                            node = node.nextSibling();
                            break;
                        }
                    }
                }
            } while(node != null && node != until);
        }
        return total;
    }

    public static int length(Node node){ return functional.html.length(node, node); }

    public static void traverse(Node node, Visitor visitor) { functional.html.traverse(node, node, visitor); }

    public static void traverse(Node node, Node until, Visitor visitor) {
        if(node == null || visitor == null){
            throw new RuntimeException("invalid parameter exception");
        }
        int start = 0;
        int end = functional.html.length(node);
        int depth = 0;
        do {
            if(visitor.on(start, end, depth, node)) {
                if(functional.html.has.children(node)) {
                    node = functional.html.begin(node.childNodes());
                    end = start + functional.html.length(node);
                } else if(functional.html.has.next(node)) {
                    if(node != until) {
                        start = start + functional.html.length(node);
                        node = node.nextSibling();
                        end = start + functional.html.length(node);
                    }
                } else {
                    while(node != null && node != until) {
                        if(node.parent() != null) {
                            int distance = functional.html.distance(node.parent(), node);
                            start -= distance;
                        }
                        node = node.parent();
                        if(node != null && node != until && node.nextSibling() != null) {
                            start = start + functional.html.length(node);
                            node = node.nextSibling();
                            end = start + functional.html.length(node);
                            break;
                        }
                    }
                }
                continue;
            }
            break;
        } while(node != null && node != until);
    }

    public static Triple<Node, Integer, Integer> find(Node node, int index) { return functional.html.find(node, node, index); }

    public static Triple<Node, Integer, Integer> find(Node node, Node until, int index) {
        if(node == null || index < 0) {
            throw new RuntimeException("invalid parameter exception");
        }
        Triple<Node, Integer, Integer> found = new Triple<>();
        traverse(node, until, (start, end, depth, n) -> {
            if(start <= index && index < end && functional.html.is.leaf(n)) {
                found.set(n, start, end);
                return false;
            }
            return true;
        });
        return found;
    }

    public static Triple<Node, Integer, Integer> find(Node node, int from, int to) {
        if(node == null || from < 0 || to <= from) {
            throw new RuntimeException("");
        }
        Triple<Node, Integer, Integer> found = functional.html.find(node, from);
        if(functional.tuple.exist(found)) {
            while(functional.tuple.exist(found) && found.first() != node && found.third() <= to) {
                int distance = functional.html.distance(functional.html.parent(found.first()), found.first());
                found.first(functional.html.parent(found.first()));
                found.second(found.second() - distance);
                found.third(found.second() + functional.html.length(found.first()));
            }
            if(functional.tuple.exist(found)) {
                if(from < found.second()) {
                    throw new RuntimeException("");
                }
                /**
                 * found.third() <= to 보다 큰 경우는 존재한다.
                 * 즉, 한 라인보다 더 큰 경우이다.
                 */
                return found;
            }
        }
        return null;
    }

    public static void set(TextNode node, String v) {
        if(node == null) {
            throw new RuntimeException("");
        }
        node.text(v != null ? v : "");
    }

    public static void set(Element element, Mark mark) {
        if(element != null && mark != null) {
            if(functional.string.equal(element.nodeName(), mark.tag())) {
                if(mark.attrs() != null) {
                    for(Attr attr : mark.attrs()) {
                        element.attr(attr.name(), attr.value());
                    }
                }
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static void before(Node node, String v) {
        if(!functional.string.empty(v)) {
            if(node instanceof TextNode) {
                functional.html.set((TextNode) node, functional.html.to.text(v, functional.html.is.pre(node.parent())) + functional.html.to.text(node, functional.html.is.pre(node.parent())));
            } else if(node != null) {
                node.before(new TextNode(functional.html.to.text(v, false)));
            }
        }
    }

    public static void before(TextNode node, TextNode n) {
        functional.html.set(node, functional.html.to.text(n, functional.html.is.pre(node.parent())) + functional.html.to.text(node, functional.html.is.pre(node.parent())));
    }

    public static void before(Node node, Node n) {
        if(node instanceof TextNode && n instanceof TextNode) {
            functional.html.before((TextNode) node, (TextNode) n);
        } else if(node != null) {
            if(n != null) {
                node.before(n);
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static void after(Node node, String v) {
        if(!functional.string.empty(v)) {
            if(node instanceof TextNode) {
                functional.html.set((TextNode) node, functional.html.to.text(node, functional.html.is.pre(node.parent())) + functional.html.to.text(v, functional.html.is.pre(node.parent())));
            } else if(node != null) {
                node.after(new TextNode(functional.html.to.text(v, functional.html.is.pre(node.parent()))));
            }
        }
    }

    public static void after(TextNode node, TextNode n) {
        functional.html.set(node, functional.html.to.text(node, functional.html.is.pre(node.parent())) + functional.html.to.text(n, functional.html.is.pre(node.parent())));
    }

    public static void after(Node node, Node n) {
        if(node instanceof TextNode && n instanceof TextNode) {
            functional.html.after((TextNode) node, (TextNode) n);
        } else if(node != null) {
            if(n != null) {
                node.after(n);
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static void prepend(Element parent, String v) {
        if(!functional.string.empty(v)) {
            if(parent == null) {
                throw new RuntimeException("");
            }
            Node begin = functional.html.begin(parent.childNodes());
            if(begin instanceof TextNode) {
                functional.html.before((TextNode) begin, new TextNode(v));
            } else {
                parent.prependChild(new TextNode(v));
            }
        }
    }

    public static void prepend(Element parent, List<? extends Node> children) {
        if(parent == null) {
            throw new RuntimeException("");
        }
        if(functional.list.exist(children)) {
            children = new ArrayList<>(children);
            for(int i = children.size() - 1; i >= 0; i--) {
                functional.html.prepend(parent, children.get(i));
            }
        }
    }

    public static void prepend(Element parent, Node child) {
        if(parent == null) {
            throw new RuntimeException("");
        }
        if(child instanceof TextNode) {
            Node begin = functional.html.begin(parent.childNodes());
            if(begin instanceof TextNode) {
                functional.html.before((TextNode) begin, (TextNode) child);
            } else {
                parent.prependChild(child);
            }
        } else if(child != null) {
            parent.prependChild(child);
        }
    }

    public static void append(Element parent, Node child) {
        if(parent == null) {
            throw new RuntimeException("");
        }
        if(child instanceof TextNode) {
            Node end = functional.html.end(parent.childNodes());
            if(end instanceof TextNode) {
                functional.html.after((TextNode) end, (TextNode) child);
            } else {
                parent.appendChild(child);
            }
        } else if(child != null) {
            parent.appendChild(child);
        }
    }

    public static void append(Element parent, List<Node> children) {
        if(parent == null) {
            throw new RuntimeException("");
        }
        if(functional.list.exist(children)) {
            children = new ArrayList<>(children);
            for(Node child : children) {
                functional.html.append(parent, child);
            }
        }
    }

    public static List<Element> clone(List<Element> elements) {
        LinkedList<Element> o = new LinkedList<>();
        for(Element element : elements) {
            o.add(element.clone());
        }
        return o;
    }

    public static Document clone(Document document) {
        Document o = null;
        if(document != null) {
            o = document.clone();
            return __adjustor != null ? __adjustor.document(o) : o;
        }
        return o;
    }

    public static Node clone(Node node, boolean children) { return node != null ? (children ? node.clone() : node.shallowClone()) : null; }

    public static Element clone(Element node, boolean children) { return node != null ? (children ? node.clone() : node.shallowClone()) : null; }

    public static Node clone(Node original, Node begin, Node until, Node replacement) {
        if(original == null) {
            throw new RuntimeException("");
        }
        if(begin == null && until != null) {
            Node destination = functional.html.clone(original, false);
            Node node = destination;
            Node current = original;
            do {
                if(functional.html.has.children(current)) {
                    current = functional.html.begin(current.childNodes());
                    if(current != until && current != original) {
                        Node clone = functional.html.clone(current, false);
                        if(functional.html.is.appendable(node)) {
                            functional.html.append((Element) node, clone);
                            node = clone;
                        } else {
                            throw new RuntimeException("");
                        }
                    } else {
                        if(functional.html.is.appendable(node)) {
                            functional.html.append((Element) node, replacement);
                        } else {
                            throw new RuntimeException("");
                        }
                    }
                } else {
                    if(functional.html.has.next(current)) {
                        current = current.nextSibling();
                    } else {
                        while(current != until && current != original && current.nextSibling() == null) {
                            current = current.parent();
                            node = node.parent();
                        }
                        if(current.nextSibling() != null) {
                            current = current.nextSibling();
                        }
                    }
                    if(current != until && current != original) {
                        Node clone = functional.html.clone(current, false);
                        functional.html.after(node, clone);
                        node = clone;
                    } else {
                        functional.html.after(node, replacement);
                    }
                }
            } while(current != until && current != original);
            return destination;
        } else if(begin != null && until == null) {
            Node destination = replacement;
            Node current = begin;
            List<Node> nodes = new LinkedList<>();
            nodes.add(destination);
            while(current != original) {
                if(functional.html.has.next(current)) {
                    current = current.nextSibling();
                    nodes.add(destination = functional.html.clone(current, true));
                } else {
                    current = current.parent();
                    if(current == null) {
                        throw new RuntimeException("");
                    }
                    Node parent = functional.html.clone(current, false);
                    functional.html.append((Element) parent, nodes);
                    nodes.clear();
                    nodes.add(destination = parent);
                }
            }
            if(destination == null) {
                functional.html.append((Element) (destination = functional.html.clone(original, false)), nodes);
            }
            return destination;
        } else {
            throw new RuntimeException("invalid parameter exception");
        }
    }

    public static List<Node> split(Node node, int index) {
        Triple<Node, Integer, Integer> found = functional.html.find(node, index);
        if(functional.tuple.exist(found)) {
            if(found.first() instanceof TextNode) {
                String s = functional.html.to.text((TextNode) found.first(), functional.html.is.pre(functional.html.parent(found.first())));
                List<String> strings = functional.string.split(s, index - found.second());
                if(strings.size() == 2) {
                    Node first = functional.html.clone(node, null, found.first(), new TextNode(strings.get(0)));
                    Node second = functional.html.clone(node, found.first(), null, new TextNode(strings.get(1)));
                    return functional.list.gen(first, second);
                } else {
                    throw new RuntimeException("");
                }
            } else if(index == found.second()) {
                return functional.list.gen(null, functional.html.clone(found.first(), true));
            } else {
                throw new RuntimeException("");
            }
        } else if(functional.html.is.end(node, index)) {
            Node end = functional.html.adjust.end(node);
            return functional.list.gen(functional.html.clone(end, true), (Node) null);
        } else {
            System.out.println("index: " + index);
            System.out.println("length: " + functional.html.length(node));
            System.out.println("node: " + node);
            throw new RuntimeException("");
        }
    }

    public static List<Node> split(Node node, int from, int to) {
        List<Node> first = functional.html.split(node, from);
        if(functional.list.size(first) == 2) {
            if(first.get(1) != null) {
                List<Node> second = functional.html.split(first.get(1), to - from);
                if(functional.list.size(second) == 2) {
                    return functional.list.gen(first.get(0), second.get(0), second.get(1));
                } else {
                    throw new RuntimeException("");
                }
            } else if(from == to) {
                return functional.list.gen(first.get(0), null, null);
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static void remove(Node node) {
        if(node != null) {
            node.remove();
        }
    }

    public static void remove(List<Node> nodes) {
        if(functional.list.exist(nodes)) {
            nodes = new ArrayList<>(nodes);
            for(Node node : nodes) {
                functional.html.remove(node);
            }
        }
    }

    public static void insert(Node node, int index, String v) {
        Triple<Node, Integer, Integer> found = functional.html.find(node, index);
        if(functional.tuple.exist(found)) {
            if(found.first() instanceof TextNode) {
                String s = functional.html.to.text((TextNode) found.first(), functional.html.is.pre(functional.html.parent(found.first())));
                System.out.println(s);
                s = functional.string.insert(s, index, v);
                System.out.println(s);
                functional.html.set((TextNode) found.first(), functional.html.to.text(s, functional.html.is.pre(functional.html.parent(found.first()))));
            } else if(functional.html.is.br(found.first())) {
                functional.html.before(found.first(), v);
            } else if(index == 0) {
                functional.html.prepend((Element) found.first(), v);
            } else {
                throw new RuntimeException("");
            }
        } else if(functional.html.is.end(node, index)) {
            Node end = functional.html.adjust.end(node);
            if(end instanceof Element) {
                functional.html.append((Element) end, new TextNode(functional.html.to.text(v, functional.html.is.pre(end))));
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static void replace(Node node, Node n) {
        Node prev = node.previousSibling();
        Node parent = node.parent();
        if(prev != null) {
            node.remove();
            functional.html.after(prev, n);
        } else if(parent instanceof Element) {
            node.remove();
            functional.html.prepend((Element) parent, n);
        } else {
            throw new RuntimeException("");
        }
    }

    public static void replace(Node node, List<? extends Node> nodes) {
        if(functional.list.exist(nodes)) {
            Node next = node.nextSibling();
            Node parent = node.parent();
            if(next != null) {
                node.remove();
                nodes = new ArrayList<>(nodes);
                for(int i = nodes.size() - 1; i >= 0; i--) {
                    functional.html.before(next, nodes.get(i));
                    if(!(next instanceof TextNode && nodes.get(i) instanceof TextNode)) {
                        next = nodes.get(i);
                    }
                }
            } else if(parent instanceof Element) {
                node.remove();
                functional.html.prepend((Element) parent, nodes);
            } else {
                throw new RuntimeException("");
            }
        }
    }

    public static void replace(TextNode node, int from, int to, String v) {
        if(node != null) {
            String s = functional.string.replace(functional.html.to.text(node, functional.html.is.pre(node.parent())), from, to, functional.html.to.text(v, functional.html.is.pre(node.parent())));
            functional.html.set(node, s);
        } else {
            throw new RuntimeException("");
        }
    }

    public static void replace(Node node, int from, int to, String v) {
        if(from < to) {
            Triple<Node, Integer, Integer> found = functional.html.find(node, from, to);
            if(functional.tuple.exist(found)) {
                if(found.first() instanceof TextNode) {
                    functional.html.replace((TextNode) found.first(), from - found.second(), to - found.second(), v);
                } else if(functional.html.is.br(found.first())) {
                    if(from + 1 == to) {
                        functional.html.replace(found.first(), new TextNode(functional.html.to.text(v, false)));
                    } else {
                        throw new RuntimeException("");
                    }
                } else if(functional.html.is.end(found.first(), to - found.second())) {
                    List<Node> nodes = functional.html.split(found.first(), from);
                    Node current = nodes.get(0);
                    while(!functional.html.is.leaf(current)) {
                        current = functional.html.end(current.childNodes());
                    }
                    System.out.println(current);
                    System.out.println(nodes.get(0));
                    System.out.println(nodes.get(1));
                    functional.html.replace(found.first(), nodes.get(0));
                    if(current instanceof TextNode) {
                        functional.html.after(current, v);
                    } else {
                        throw new RuntimeException("");
                    }
                } else if(found.third() <= to) {
                    List<Node> nodes = functional.html.split(found.first(), from - found.second());
                    int erase;
                    if(found.first() == node) {
                        functional.html.remove(node.childNodes());
                        functional.html.append((Element) node, functional.html.children(nodes.get(0)));
                        functional.html.append((Element) node, new TextNode(functional.html.to.text(v, functional.html.is.pre(node))));
                        System.out.println("found[start]: " + found.second());
                        System.out.println("found[end]: " + found.third());
                        erase = (found.third() - from);
                    } else {
                        throw new RuntimeException("");
                    }
                    Node next = node.nextSibling();
                    System.out.println(next);
                    int length = functional.html.length(next);
                    int total = to - from;
                    while(next != null && erase + length < total) {
                        Node current = next;
                        next = next.nextSibling();
                        current.remove();
                        erase += length;
                        System.out.println("erase: " + erase);
                        System.out.println("length: " + length);
                        length = functional.html.length(next);
                    }
                    if(next != null && erase <= total) {
                        System.out.println("total: " + total);
                        nodes = functional.html.split(next, total - erase);
                        next.remove();
                        functional.html.append((Element) node, functional.html.children(nodes.get(1)));
                    } else {
                        System.out.println("next: " + next);
                        System.out.println("next: " + (next!=null ? next.nodeName() : null));
                        System.out.println("erase: " + erase);
                        System.out.println("total: " + total);
                        if(erase < total) {
                            throw new RuntimeException("");
                        }

                    }
                } else {
                    throw new RuntimeException("");
                }
            } else {
                if(from + 2 == to) {
                    if(to <= functional.html.length(node)) {
                        if(functional.html.is.appendable(node)) {
                            Node next = node.nextSibling();
                            if(next != null){
                                if(functional.string.empty(v)) {
                                    List<Node> children = next.childNodesCopy();
                                    next.remove();
                                    functional.html.append((Element) node, children);
                                } else {
                                    throw new RuntimeException(v);
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
                } else {
                    throw new RuntimeException("");
                }
            }
        } else if(from == to) {
            if(!functional.string.empty(v)) {
                functional.html.insert(node, from, v);
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static void enter(Node node, int from, int to, List<Mark> marks) {
        List<Node> nodes = functional.html.split(node, from, to);
        if(functional.list.size(nodes) == 3) {
            System.out.println("from: " + from);
            System.out.println("to: " + to);
            System.out.println("length: " + functional.html.length(node));
            Element front = functional.html.to.element(marks.get(0), functional.html.children(nodes.get(0), true));
            Element end = functional.html.to.element(marks.get(1), functional.html.children(nodes.get(2), true));
            functional.html.replace(node, front);
            front.after(end);
            System.out.println("front: " + front);
            System.out.println("end: " + end);
        } else {
            throw new RuntimeException("");
        }
    }

    public static void unmark(Node node, int from, int to, Mark mark) {
        Triple<Node, Integer, Integer> found = functional.html.find(node, from, to);
        if(functional.tuple.exist(found)) {
            while(found.first() != node && !functional.html.has.prev(found.first()) && !functional.html.has.next(found.first())) {
                Node parent = functional.html.parent(found.first());
                if(parent != node) {
                    found.first(parent);
                }
            }
            LinkedList<Triple<Node, Integer, Integer>> children = new LinkedList<>();
            functional.html.traverse(found.first(), (start, end, depth, n) -> {
                if(n != found.first()) {
                    if(functional.html.equal(n, mark)) {
                        children.add(new Triple<>(n, start + found.second(), end + found.second()));
                    }
                }
                return true;
            });
            if(functional.html.equal(found.first(), mark)) {
                children.add(new Triple<>(found.first(), found.second(), found.third()));    // CHECK THIS LOGIC
            }
            for(Triple<Node, Integer, Integer> n : children) {
                System.out.println("triple: " + n.first());
                System.out.println("start: " + n.second());
                System.out.println("end: " + n.third());
                System.out.println("from: " + from);
                System.out.println("to: " + to);
                System.out.println("name: " + functional.html.name(n.first()));
                System.out.println("mark: " + functional.json.from(mark));
                if(from <= n.second() && n.third() <= to) {
                    functional.html.replace(n.first(), functional.html.children(n.first()));
                } else {
                    List<Node> replacement = null;
                    if(n.first() != node) {
                        if(from <= n.second()) {
                            if(n.second() < to && to < n.third()) {
                                System.out.println("split[2]: unmark[0]");
                                List<Node> nodes = functional.html.split(n.first(), to - n.second());
                                if(functional.list.size(nodes) == 2) {
                                    replacement = new LinkedList<>(functional.html.children(nodes.get(0)));
                                    replacement.add(nodes.get(1));
                                } else {
                                    throw new RuntimeException("");
                                }
                            } else {
                                System.out.println("skip");
                            }
                        } else {
                            if(from < n.third() && n.third() <= to) {
                                System.out.println("split[2]: unmark[1]");
                                List<Node> nodes = functional.html.split(n.first(), from - n.second());
                                if(functional.list.size(nodes) == 2) {
                                    replacement = new LinkedList<>();
                                    replacement.add(nodes.get(0));
                                    replacement.addAll(functional.html.children(nodes.get(1)));
                                } else {
                                    throw new RuntimeException("");
                                }
                            } else if(to < n.third()) {
                                System.out.println("split[3]: unmark[1]");
                                List<Node> nodes = functional.html.split(n.first(), from - n.second(), to - n.second());
                                if(functional.list.size(nodes) == 3) {
                                    System.out.println("node[0]: " + nodes.get(0));
                                    System.out.println("node[1]: " + nodes.get(1));
                                    System.out.println("node[2]: " + nodes.get(2));
                                    replacement = new LinkedList<>();
                                    replacement.add(nodes.get(0));
                                    replacement.addAll(functional.html.children(nodes.get(1)));
                                    replacement.add(nodes.get(2));
                                } else {
                                    throw new RuntimeException("");
                                }
                            } else {
                                System.out.println("skip");
                            }
                        }
                        functional.html.print(replacement);
                        functional.html.replace(n.first(), replacement);
                    } else {
                        throw new RuntimeException("");
                    }
                }
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static void mark(Node node, int from, int to, Mark mark) {
        Triple<Node, Integer, Integer> found = functional.html.find(node, from, to);
        if(functional.tuple.exist(found)) {
            if(found.first() instanceof TextNode) {
                List<String> strings = functional.string.split(functional.html.to.text(found.first(), false), from - found.second(), to - found.second());
                if(functional.list.size(strings) == 3) {
                    functional.html.set((TextNode) found.first(), functional.html.to.text(strings.get(0), false));
                    Node n = functional.html.to.element(mark, new TextNode(functional.html.to.text(strings.get(1), false)));
                    functional.html.after(found.first(), n);
                    functional.html.after(n, new TextNode(functional.html.to.text(strings.get(2), false)));
                } else {
                    throw new RuntimeException("");
                }
            } else if(functional.html.is.br(found.first())) {
                functional.html.replace(found.first(), functional.html.to.element(mark, functional.html.clone(found.first(), false)));
            } else {
                List<Node> nodes = functional.html.split(found.first(), from - found.second(), to - found.second());
                if(functional.list.size(nodes) == 3) {
                    if(found.first() == node) {
                        nodes.set(1, functional.html.to.element(mark, functional.html.children(nodes.get(1))));
                        functional.html.remove(node.childNodes());
                        functional.html.append((Element) node, functional.html.children(nodes.get(0)));
                        functional.html.append((Element) node, nodes.get(1));
                        functional.html.append((Element) node, functional.html.children(nodes.get(2)));
                    } else {
                        nodes.set(1, functional.html.to.element(mark, nodes.get(1)));
                        functional.html.replace(found.first(), nodes);
                    }
                } else {
                    throw new RuntimeException("");
                }
            }
        } else {
            throw new RuntimeException();
        }
    }

    public static List<Element> unaround(Element element, int from, int to) {
        if(element != null) {
            int length = functional.html.length(element);
            System.out.println("element: " + element);
            System.out.println("from: " + from);
            System.out.println("to: " + to);
            System.out.println("length: " + length);
            if(to - from == length) {

            } else {
                System.err.println("UNAROUND MULTI LINE");
            }
            throw new RuntimeException("");
        } else {
            throw new RuntimeException("");
        }
//        if(element != null) {
//            if(to - from == functional.html.length(element)) {
//                if(functional.html.is.list(element)) {
//                    LinkedList<Node> children = new LinkedList<>(element.select("li"));
//                    functional.html.replace(element, children);
//                } else {
//                    functional.html.replace(element, element.childNodes());
//                }
//            } else {
//                throw new RuntimeException("");
//            }
//        } else {
//            throw new RuntimeException("");
//        }
    }

    public static Element around(Element element, int from, int to, Mark mark) {


        if(element != null) {
            if(mark != null) {
                int length = functional.html.length(element);
                if(to - from == length) {
                    if(from == -1) {
                        List<Node> children = functional.html.children(mark, element);
                        Element o = functional.html.to.element(mark, children);
                        functional.html.replace(element, o);
                        return o;
                    } else {
                        throw new RuntimeException("");
                    }
                } else {
                    if(functional.html.is.block(mark)) {
                        if(functional.html.is.list(mark) || functional.html.is.order(mark)) {
                            throw new RuntimeException("implement this");
                        }
                        if(from == -1) {
                            int total = to - from;
                            int erase = 0;
                            List<Node> children = new LinkedList<>();
                            Node current = element;
                            do {
                                System.out.println(current);
                                children.add(current);
                                erase += length;
                                current = current.nextSibling();
                                if(current == null) {
                                    throw new RuntimeException("");
                                }
                                length = functional.html.length(current);
                            } while(erase < total);
                            if(erase != total) {
                                throw new RuntimeException("");
                            }
                            Element o = functional.html.to.element(mark, children, true);
                            for(Node n : children) {
                                if(n != element) {
                                    n.remove();
                                }
                            }
                            functional.html.replace(element, o);
                            return o;
                        } else {
                            throw new RuntimeException("");
                        }
                    } else {
                        throw new RuntimeException("");
                    }
                }
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }
}
