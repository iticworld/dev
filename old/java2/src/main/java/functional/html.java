package functional;

import hornet.editor.html.Adapter;
import hornet.editor.html.Attr;
import hornet.editor.html.Mark;
import hornet.editor.html.Visitor;

import novemberizing.tuple.Triple;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.nodes.Node;
import org.jsoup.nodes.TextNode;

import java.util.ArrayList;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;

@SuppressWarnings("WeakerAccess")
public class html {
    public static class validate {
        public static boolean tag(String v){ return !functional.string.empty(v); }
    }

    public static class adjust {
        public static Triple<Element, Integer, Integer> element(Element element, int index) {
            if(__adapter != null) {
                return __adapter.adjust(element, index);
            }
            return new Triple<>(element, 0, functional.html.length(element));
        }
        public static String html(String html){
            if(__adapter != null) {
                html = __adapter.adjust(html);
            }
            return html;
        }

        public static Document document(Document document) {
            if(__adapter != null) {
                document = __adapter.adjust(document);
            }
            return document;
        }
        public static int length(String name){
            if(__adapter != null) {
                return __adapter.length(name);
            }
            return 0;
        }

        public static int index(Element element, int index){
            if(__adapter != null) {
                return __adapter.index(element, index);
            }
            return index;
        }

        public static String name(String v) {
            if(__adapter != null) {
                return __adapter.name(v);
            }
            return v;
        }
    }

    public static class to {
        public static Document document(String html) {
            return functional.html.adjust.document(Jsoup.parse(functional.string.v(html)));
        }

        public static String string(Element element, boolean in) {
            return element != null ? (in  ? element.html() : element.outerHtml()) : "";
        }

        public static Element element(Mark mark) {
            if(mark != null) {
                Element element = new Element(functional.html.adjust.name(mark.name()));
                Collection<Attr> collection = mark.attrs();
                if(functional.collection.exist(collection)) {
                    for(Attr attr : collection) {
                        if(attr != null) {
                            element.attr(attr.name(), attr.value());
                        }
                    }
                }
                return element;
            } else {
                throw new RuntimeException("");
            }
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
                        element.appendChild(clone ? child.clone() : child);
                    } else {
                        System.err.println("child is null");
                    }
                }
            } else {
                System.err.println("nodes is empty");
            }
            return element;
        }
    }

    public static class has {
        public static boolean children(Node node) { return node != null && functional.list.size(node.childNodes()) > 0; }
        public static boolean next(Node node){ return node != null && node.nextSibling() != null; }
        public static boolean prev(Node node){ return node != null && node.previousSibling() != null; }
    }

    public static class is {
        public static boolean end(Node node, int index) {
            if(node != null) {
                return index == functional.html.length(node);
            } else if(index > 0 || index < 0) {
                throw new RuntimeException("");
            }
            return false;
        }
        public static boolean appendable(Node node){ return !(node instanceof TextNode) && !functional.html.is.br(node); }
        public static boolean leaf(Node node){ return !functional.html.has.children(node); }
        public static boolean br(Node node){ return node != null && functional.string.equal(node.nodeName(), "br"); }

        public static boolean code(Node node){ return node != null && functional.string.equal(node.nodeName(), "code"); }
    }

    private static Adapter __adapter;

    public static void init(Adapter adapter) {
        synchronized (html.class) {
            if(__adapter == null) {
                __adapter = adapter;
            }
        }
    }

    public static String get(TextNode node){ return node != null ? node.getWholeText() : ""; }
    public static void set(TextNode node, String v){
        if(node != null) {
            node.text(functional.string.v(v));
        }
    }
    public static String name(Node node){ return node != null ? node.nodeName() : null; }
    public static String id(Node node){ return node != null ? node.attr("id") : null; }

    public static Node begin(Node node, boolean leaf) {
        if(leaf) {
            while(functional.html.has.children(node)) {
                node = functional.html.begin(node);
            }
            return node;
        }
        return functional.html.begin(node);
    }
    public static Element begin(Element element){
        if(element != null) {
            return functional.list.size(element.children()) > 0 ? element.child(0) : null;
        }
        return null;
    }
    public static Node begin(Node node){ return node != null ? functional.list.begin(node.childNodes()) : null; }
    public static Node end(Node node){ return node != null ? functional.list.end(node.childNodes()) : null; }
    public static Node end(Node node, boolean leaf) {
        if(leaf) {
            while(functional.html.has.children(node)) {
                node = functional.html.end(node);
            }
            return node;
        }
        return functional.html.end(node);
    }
    public static Element parent(Node node){ return node != null ? (node.parent() instanceof Element ? (Element) node.parent() : null) : null; }

    public static List<Node> children(Node node){ return node != null ? node.childNodes() : null; }
    public static List<Node> children(Node node, boolean clone) {
        if(node != null) {
            return clone ? node.childNodesCopy() : node.childNodes();
        }
        return null;
    }

    public static boolean equal(Node node, Attr attr) {
        if(node != null && attr != null) {
            String v = node.attr(attr.name());
            return functional.string.equal(v, attr.value());
        } else {
            throw new RuntimeException("");
        }
    }

    public static boolean equal(Node node, Collection<Attr> attrs) {
        if(node != null) {
            if(functional.collection.exist(attrs)) {
                for(Attr attr : attrs) {
                    if(attr != null) {
                        if(!functional.html.equal(node, attr)) {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        throw new RuntimeException("");
    }

    public static boolean equal(Node node, Mark mark) {
        if(node != null && mark != null) {
            if(functional.html.validate.tag(mark.name())) {
                if(functional.string.equal(mark.name(), node.nodeName())) {
                    return functional.html.equal(node, mark.attrs());
                }
            } else {
                return functional.html.equal(node, mark.attrs());
            }
            return false;
        } else {
            throw new RuntimeException("");
        }
    }

    public static int length(TextNode node) {
        if(node != null) {
            String s = node.getWholeText();
            s = s.replace("&nbsp;", " ");
            s = s.replace("&gt;", "<");
            s = s.replace("&lt;", ">");
            s = s.replace("&amp;", "&");
            return s.length();
        }
        return 0;
    }

    public static int length(Node node, Node until) {
        int total = 0;
        if(node != null) {
            do {
                if(functional.html.is.leaf(node)) {
                    if(node instanceof TextNode) {
                        total += functional.html.length((TextNode) node);
                    } else if(functional.html.is.br(node)) {
                        total += 1;
                    } else {
                        total += functional.html.adjust.length(node.nodeName());
                    }
                } else {
                    total += functional.html.adjust.length(node.nodeName());
                }
                if(functional.html.has.children(node)) {
                    node = functional.html.begin(node);
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

    public static int length(Node node) { return functional.html.length(node, node); }

    public static int distance(Node parent, Node child) {
        if(parent == null || child == null) {
            throw new RuntimeException("");
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
        throw new RuntimeException("");
    }

    public static Document clone(Document document) {
        if(document != null) {
            Document o = document.clone();
            Document.OutputSettings settings = o.outputSettings();
            settings.prettyPrint(false);
            settings.indentAmount(0);
            o.outputSettings(settings);
            return functional.html.adjust.document(o);
        } else {
            throw new RuntimeException("");
        }
    }

    public static Node clone(Node node, boolean children) { return node != null ? (children ? node.clone() : node.shallowClone()) : null; }

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
                    current = functional.html.begin(current);
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

    public static void traverse(Node node, Visitor visitor){ traverse(node, node, visitor); }

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
                    node = functional.html.begin(node);
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
        functional.html.traverse(node, until, (start, end, depth, n) -> {
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
            while(functional.tuple.exist(found) && found.first() != node && found.third() < to) {
                int distance = functional.html.distance(functional.html.parent(found.first()), found.first());
                found.first(functional.html.parent(found.first()));
                found.second(found.second() - distance);
                found.third(found.second() + functional.html.length(found.first()));
            }
            if(functional.tuple.exist(found)) {
                if(from < found.second()) {
                    throw new RuntimeException("");
                }
                return found;
            }
        }
        return null;
    }

    public static void remove(List<Node> nodes) {
        if(functional.list.exist(nodes)) {
            nodes = new ArrayList<>(nodes);
            for(Node node : nodes) {
                node.remove();;
            }
        }
    }

    public static void prepend(Element element, String v) {
        Node begin = functional.html.begin(element);
        if(begin instanceof TextNode) {
            functional.html.before((TextNode) begin, v);
        } else {
            element.prependChild(new TextNode(functional.string.v(v)));
        }
    }

    public static void prepend(Element element, Node n) {
        Node begin = functional.html.begin(element);
        if(begin instanceof TextNode && n instanceof TextNode) {
            functional.html.before((TextNode) begin, (TextNode) n);
        } else {
            element.prependChild(n);
        }
    }

    public static void prepend(Element element, List<? extends Node> children) {
        if(element != null) {
            if(functional.list.exist(children)) {
                children = new ArrayList<>(children);
                for(int i = children.size() - 1; i >= 0; i--) {
                    functional.html.prepend(element, children.get(i));
                }
            }
        }
    }

    public static void append(Element element, String v) {
        Node end = functional.html.end(element);
        if(end instanceof TextNode) {
            functional.html.after((TextNode) end, v);
        } else {
            element.appendChild(new TextNode(functional.string.v(v)));
        }
    }

    public static void append(Element element, List<Node> nodes) {
        if(element != null) {
            if(functional.list.exist(nodes)) {
                nodes = new ArrayList<>(nodes);
                for(Node child : nodes) {
                    functional.html.append(element, child);
                }
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static void append(Element element, Node n) {
        Node end = functional.html.end(element);
        if(end instanceof TextNode && n instanceof TextNode) {
            functional.html.after((TextNode) end, (TextNode) n);
        } else {
            element.appendChild(n);
        }
    }

    @SuppressWarnings("Duplicates")
    public static void before(TextNode node, String v) {
        if(node != null) {
            if(functional.string.exist(v)) {
                String s = node.getWholeText();
                node.text(v + s);
            }
        } else {
            throw new RuntimeException("");
        }
    }

    @SuppressWarnings("Duplicates")
    public static void before(TextNode node, TextNode n) {
        if(node != null && n != null) {
            String first = node.getWholeText();
            String second = n.getWholeText();
            node.text(second + first);
        } else {
            throw new RuntimeException("");
        }
    }

    public static void before(Node node, String v) {
        if(node instanceof TextNode) {
            functional.html.before((TextNode) node, v);
        } else if(node != null) {
            node.before(new TextNode(functional.string.v(v)));
        } else {
            throw new RuntimeException("");
        }
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

    @SuppressWarnings("Duplicates")
    public static void after(TextNode node, String v) {
        if(node != null) {
            if(functional.string.exist(v)) {
                String s = node.getWholeText();
                node.text(s + v);
            }
        } else {
            throw new RuntimeException("");
        }
    }

    @SuppressWarnings("Duplicates")
    public static void after(TextNode node, TextNode n) {
        if(node != null && n != null) {
            String first = node.getWholeText();
            String second = n.getWholeText();
            node.text(first + second);
        } else {
            throw new RuntimeException("");
        }
    }

    public static void after(Node node, String v) {
        if(node instanceof TextNode) {
            functional.html.after((TextNode) node, v);
        } else if(node != null) {
            node.after(new TextNode(functional.string.v(v)));
        } else {
            throw new RuntimeException("");
        }
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

    public static List<Node> split(Node node, int index) {
        Triple<Node, Integer, Integer> found = functional.html.find(node, index);
        if(functional.tuple.exist(found)) {
            if(found.first() instanceof TextNode) {
                String s = functional.html.get((TextNode) found.first());
                List<String> strings = functional.string.split(s, index - found.second());
                if(strings.size() == 2) {
                    Node first = functional.html.clone(node, null, found.first(), new TextNode(functional.string.v(strings.get(0))));
                    Node second = functional.html.clone(node, found.first(), null, new TextNode(functional.string.v(strings.get(1))));
                    return functional.list.gen(first, second);
                } else {
                    throw new RuntimeException("");
                }
            } else if(index == found.second()) {
                return functional.list.gen(null, functional.html.clone(found.first(), true));
            } else {
                throw new RuntimeException("");
            }
        } else if(functional.html.length(node) == index + functional.html.adjust.length(node.nodeName())) {
            Node first = functional.html.clone(node, true);
            return functional.list.gen(functional.html.clone(first, true), (Node) null);
        } else {
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

    public static void insert(Element element, int index, String v) {
        if(element != null) {
            if(index == 0) {
                Node begin = functional.html.begin(element, true);
                if(begin instanceof TextNode) {
                    functional.html.before((TextNode) begin, v);
                } else if(functional.html.is.br(begin)) {
                    functional.html.before(begin, v);
                } else if(begin != null) {
                    functional.html.prepend((Element) begin, v);
                } else {
                    throw new RuntimeException("");
                }
            } else {
                Triple<Node, Integer, Integer> found = functional.html.find(element, index);
                if(functional.tuple.exist(found)) {
                    if(found.first() instanceof TextNode) {
                        TextNode node = (TextNode) found.first();
                        String s = functional.string.insert(node.getWholeText(), index - found.second(), v);
                        node.text(s);
                    } else if(functional.html.is.br(found.first())) {
                        functional.html.before(found.first(), v);
                    } else {
                        throw new RuntimeException("");
                    }
                } else if(functional.html.length(element) == index + functional.html.adjust.length(element.nodeName())) {
                    Node end = functional.html.end(element, true);
                    if(end != null) {
                        functional.html.after(end, v);
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
                        if(nodes.get(i) != null) {
                            next = nodes.get(i);
                        }
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
            String s = functional.string.replace(node.getWholeText(), from, to, functional.string.v(v));
            node.text(s);
        } else {
            throw new RuntimeException("");
        }
    }

    public static void replace(Element element, int from, int to, String v) {
        int length = functional.html.length(element);
        if(to <= length) {
            if(from == 0 && to == length) {
                throw new RuntimeException("");
            } else {
                Triple<Node, Integer, Integer> found = functional.html.find(element, from, to);
                if(functional.tuple.exist(found)) {
                    if(found.first() instanceof TextNode) {
                        functional.html.replace((TextNode) found.first(), from - found.second(), to - found.second(), v);
                    } else if(functional.html.is.br(found.first())) {
                        if(from + 1 == to) {
                            functional.html.replace(found.first(), new TextNode(functional.string.v(v)));
                        } else {
                            throw new RuntimeException("");
                        }
                    } else {
                        List<Node> nodes = functional.html.split(found.first(), from - found.second(), to - found.second());
                        if(found.first() == element) {
                            // nodes.set(0, functional.html.children(nodes.get(0)));
                            // nodes.set(1, functional.string.empty(v) ? null : new TextNode(v));
                            functional.html.remove(element.childNodes());
                            functional.html.append(element, functional.html.children(nodes.get(0)));
                            if(functional.string.exist(v)) {
                                functional.html.append(element, new TextNode(functional.string.v(v)));
                            }
                            functional.html.append(element, functional.html.children(nodes.get(2)));
                        } else {
                            nodes.set(1, functional.string.empty(v) ? null : new TextNode(v));
                            functional.html.replace(found.first(), nodes);
                        }
                    }
                } else {
                    throw new RuntimeException("");
                }
            }
        } else {
            int total = (to - from);
            int erase = 0;
            Element front = null;
            Element next = element.nextElementSibling();
            if(from != 0) {
                List<Node> nodes = functional.html.split(element, from);
                if(nodes.get(0) instanceof Element) {
                    functional.html.replace(element, front = (Element) nodes.get(0));
                    if(functional.string.exist(v)) {
                        Node end = functional.html.end(front, true);
                        if(end != null) {
                            if(functional.html.is.appendable(end)) {
                                functional.html.append((Element) end, v);
                            } else {
                                functional.html.after(end, v);
                            }
                        } else {
                            throw new RuntimeException("");
                        }
                    }
                    element = front;
                    erase = (length - from);
                } else {
                    throw new RuntimeException("");
                }
            } else if(functional.string.exist(v)) {
                functional.html.remove(element.childNodes());
                functional.html.append(element, new TextNode(v));
                front = element;
                erase = length;
            } else {
                element.remove();
                erase = length;
            }
            if(next != null) {
                length = functional.html.length(next);
                while(erase < total) {
                    if(erase + length < total) {
                        Element current = next;
                        next = next.nextElementSibling();
                        current.remove();
                        erase += length;
                        length = functional.html.length(next);
                    } else if(erase + length == total) {
                        Element current = next;
                        next = next.nextElementSibling();
                        current.remove();
                        if(front != null) {
                            functional.html.append(front, functional.html.children(next, true));
                        } else {
                            throw new RuntimeException("");
                        }
                        break;
                    } else {
                        int remain = total - erase;
                        List<Node> nodes = functional.html.split(next, remain);
                        if(front != null) {
                            next.remove();
                            functional.html.append(front, functional.html.children(nodes.get(1)));
                        } else {
                            functional.html.replace(next, nodes.get(1));
                        }
                        break;
                    }
                }
            } else {
                throw new RuntimeException("");
            }
        }
//        if(from == 0) {
//            throw new RuntimeException("");
//        } else {
//            Triple<Node, Integer, Integer> found = functional.html.find(element, from, to);
//            if(functional.tuple.exist(found)) {
//                if(found.first() instanceof TextNode) {
//                    functional.html.replace((TextNode) found.first(), from - found.second(), to - found.second(), v);
//                } else if(functional.html.is.br(found.first())) {
//                    if(from + 1 == to) {
//                        functional.html.replace(found.first(), new TextNode(functional.string.v(v)));
//                    } else {
//                        throw new RuntimeException("");
//                    }
//                } else {
//                    int length = functional.html.length(element);
//                    System.out.println("element: " + element);
//                    System.out.println("length: " + length);
//                    System.out.println("from: " + from);
//                    System.out.println("to: " + to);
//                    System.out.println("v: " + v);
//                    System.out.println("found.first: " + found.first());
//                    System.out.println("found.second: " + found.second());
//                    System.out.println("found.third: " + found.third());
//                    if(to < length) {
//                        if(found.first() instanceof TextNode) {
//                            throw new RuntimeException("");
//                        } else if(functional.html.is.br(found.first())) {
//                            throw new RuntimeException("");
//                        } else {
//                            List<Node> nodes = functional.html.split(found.first(), from - found.second(), to - found.second());
//                            if(functional.list.size(nodes) == 3) {
//                                if(found.first() == element) {
//                                    throw new RuntimeException("");
//                                } else {
//                                    nodes.set(1, functional.string.empty(v) ? null : new TextNode(v));
//                                    functional.html.replace(found.first(), nodes);
//                                }
//                            } else {
//                                throw new RuntimeException("");
//                            }
//                        }
//                    } else if(to == length) {
//                        throw new RuntimeException("");
//                    } else {
//                        // List<Node> nodes = functional.html.split(element, )
//                        throw new RuntimeException("");
//                    }
//
////                    throw new RuntimeException("");
//                }
//            } else {
//                throw new RuntimeException("");
//            }
//        }

//        if(from < to) {
//
//            if(functional.tuple.exist(found)) {
//                if(found.first() instanceof TextNode) {
//                    functional.html.replace((TextNode) found.first(), from - found.second(), to - found.second(), v);
//                } else if(functional.html.is.br(found.first())) {
//                    if(from + 1 == to) {
//                        functional.html.replace(found.first(), new TextNode(v));
//                    } else {
//                        throw new RuntimeException("");
//                    }
//                } else if(functional.html.is.end(found.first(), to - found.second())) {
//                    List<Node> nodes = functional.html.split(found.first(), from);
//                    Node current = functional.html.end(nodes.get(0), true);
//                    functional.html.replace(found.first(), nodes.get(0));
//                    if(current instanceof TextNode) {
//                        functional.html.after(current, v);
//                    } else {
//                        throw new RuntimeException("");
//                    }
//                } else if(found.third() <= to) {
//                    List<Node> nodes = functional.html.split(found.first(), from - found.second());
//                    int erase;
//                    if(found.first() == node) {
//                        functional.html.remove(node.childNodes());
//                        functional.html.append((Element) node, functional.html.children(nodes.get(0)));
//                        functional.html.append((Element) node, new TextNode(v));
//                        erase = (found.third() - from);
//                    } else {
//                        throw new RuntimeException("");
//                    }
//                    Node next = node.nextSibling();
//                    int length = functional.html.length(next);
//                    int total = to - from;
//                    while(next != null && erase + length < total) {
//                        Node current = next;
//                        next = next.nextSibling();
//                        current.remove();
//                        erase += length;
//                        length = functional.html.length(next);
//                    }
//                    if(next != null && erase <= total) {
//                        nodes = functional.html.split(next, total - erase);
//                        next.remove();
//                        functional.html.append((Element) node, functional.html.children(nodes.get(1)));
//                    } else {
//                        if(erase < total) {
//                            throw new RuntimeException("");
//                        }
//                    }
//                } else {
//                    throw new RuntimeException("");
//                }
//            } else {
//                if(from + 2 == to) {
//                    if(to <= functional.html.length(node)) {
//                        if(functional.html.is.appendable(node)) {
//                            Node next = node.nextSibling();
//                            if(next != null){
//                                if(functional.string.empty(v)) {
//                                    List<Node> children = next.childNodesCopy();
//                                    next.remove();
//                                    functional.html.append((Element) node, children);
//                                } else {
//                                    throw new RuntimeException(v);
//                                }
//                            } else {
//                                throw new RuntimeException("");
//                            }
//                        } else {
//                            throw new RuntimeException("");
//                        }
//                    } else {
//                        throw new RuntimeException("");
//                    }
//                } else {
//                    throw new RuntimeException("");
//                }
//            }
//        } else if(from == to) {
//            throw new RuntimeException("");
//        } else {
//            throw new RuntimeException("");
//        }
    }

    public static List<Element> enter(Element element, int index, List<Mark> marks) {
        System.out.println("element: " + element);
        System.out.println("index: " + index);
        System.out.println("mark[0]: " + functional.json.to(marks.get(0)));
        System.out.println("mark[1]: " + functional.json.to(marks.get(1)));
        if(element != null) {
            List<Node> nodes = functional.html.split(element, index);
            System.out.println("nodes[0]: " + nodes.get(0));
            System.out.println("nodes[1]: " + nodes.get(1));
            Element first = functional.html.to.element(marks.get(0), functional.html.children(nodes.get(0)));
            Element second = functional.html.to.element(marks.get(1), functional.html.children(nodes.get(1)));
            functional.html.replace(element, first);
            first.after(second);
            return functional.list.gen(first, second);
        } else {
            throw new RuntimeException("");
        }
    }

    public static void mark(Element node, int from, int to, Mark mark) {
        Triple<Node, Integer, Integer> found = functional.html.find(node, from, to);
        if(functional.tuple.exist(found)) {
            if(found.first() instanceof TextNode) {
                List<String> strings = functional.string.split(functional.html.get((TextNode) found.first()), from - found.second(), to - found.second());
                if(functional.list.size(strings) == 3) {
                    functional.html.set((TextNode) found.first(), strings.get(0));
                    Node n = functional.html.to.element(mark, new TextNode(functional.string.v(strings.get(1))));
                    functional.html.after(found.first(), n);
                    functional.html.after(n, new TextNode(functional.string.v(strings.get(2))));
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
                        functional.html.append(node, functional.html.children(nodes.get(0)));
                        functional.html.append(node, nodes.get(1));
                        functional.html.append(node, functional.html.children(nodes.get(2)));
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
                children.add(new Triple<>(found.first(), found.second(), found.third()));
            }
            for(Triple<Node, Integer, Integer> n : children) {
                if(from <= n.second() && n.third() <= to) {
                    functional.html.replace(n.first(), functional.html.children(n.first()));
                } else {
                    List<Node> replacement = null;
                    if(n.first() != node) {
                        if(from <= n.second()) {
                            if(n.second() < to && to < n.third()) {
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
                                List<Node> nodes = functional.html.split(n.first(), from - n.second());
                                if(functional.list.size(nodes) == 2) {
                                    replacement = new LinkedList<>();
                                    replacement.add(nodes.get(0));
                                    replacement.addAll(functional.html.children(nodes.get(1)));
                                } else {
                                    throw new RuntimeException("");
                                }
                            } else if(to < n.third()) {
                                List<Node> nodes = functional.html.split(n.first(), from - n.second(), to - n.second());
                                if(functional.list.size(nodes) == 3) {
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

    public static void exchange(Element front, int from, int to, Element element, Mark mark) {
        Element previous = front.previousElementSibling();
        Element parent = front.parent();
        int total = (to - from);
        int erase = 0;
        System.out.println("front: " + front);
        System.out.println("from: " + from);
        System.out.println("to: " + to);
        System.out.println("element: " + element);
        System.out.println("mark: " + functional.json.to(mark));
        System.out.println("total: " + total);
        System.out.println("erase: " + erase);
        while(erase < total) {
            int length = functional.html.length(front);
            System.out.println("erase: " + erase);
            System.out.println("total: " + total);
            System.out.println("length: " + length);
            Node current = front;
            front = front.nextElementSibling();
            current.remove();
            if(erase + length < total) {
                System.out.println("front: " + front);
            }
            erase += length;
        }
        if(previous != null) {
            Element n = functional.html.to.element(mark, element.childNodesCopy());
            element.remove();
            previous.after(n);
        } else if(parent != null) {
            Element n = functional.html.to.element(mark, element.childNodesCopy());
            element.remove();
            parent.appendChild(n);
        } else {
            throw new RuntimeException("");
        }
    }
}
