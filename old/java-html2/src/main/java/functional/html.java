package functional;

import novemberizing.html.GsonDocumentSerializer;
import novemberizing.html.GsonElementSerializer;
import novemberizing.html.GsonTextNodeSerializer;
import novemberizing.html.model.Attr;
import novemberizing.html.model.Mark;
import novemberizing.html.model.Style;
import novemberizing.tuple.Pair;
import novemberizing.tuple.Single;
import novemberizing.tuple.Triple;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.nodes.Node;
import org.jsoup.nodes.TextNode;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Locale;

public class html {
    public interface visitor { boolean on(int start, int end, int depth, Node n); }

    public static class valid {
        // todo: apply regular expression
        public static boolean tag(String v){ return v != null && !v.contains(" "); }
    }

    public static class is {
        public static boolean leaf(Node node){
            if(node != null){
                return empty(node.childNodes());
            }
            throw new RuntimeException("");
        }

        public static boolean root(Node node) {
            return node == null || node.parent() == null || functional.html.equal(node, "body");
        }
    }

    public static void id(Element element, String id, boolean force) {
        if(element != null) {
            if(force || !element.hasAttr(id)) {
                if(!functional.string.empty(id)) {
                    element.attr("id", id);
                } else {
                    element.removeAttr("id");
                }
            }
        }
    }

    public static String id(Node node) { return node != null ? node.attr("id") : null; }

    public static class has {
        public static boolean child(Node parent, Node child) {
            Single<Boolean> o = new Single<>(false);
            functional.html.traverse(parent, (start, end, depth, node) -> {
                if(node == child) {
                    o.first(true);
                    return false;
                }
                return true;
            });
            return o.first();
        }

        public static boolean next(Node node) {
            if(node != null){
                return node.nextSibling() != null;
            }
            throw new RuntimeException("");
        }

        public static boolean prev(Node node) {
            if(node != null){
                return node.previousSibling() != null;
            }
            throw new RuntimeException("");
        }

        public static boolean parent(Node node) {
            if(node != null) {
                return node.parent() != null;
            }
            throw new RuntimeException("");
        }

        public static boolean children(Node node) {
            return node != null && functional.collection.exist(node.childNodes());
        }
    }

    public static Node prev(Node node){ return node != null ? node.previousSibling() : null; }
    public static Node next(Node node){ return node != null ? node.nextSibling() : null; }
    public static Node parent(Node node){ return node != null ? node.parent() : null; }

    public static Node parent(Node node, int depth) {
        Node current = node;
        while(current != null && depth < functional.html.depth(current)) {
            current = current.parent();
        }
        return current;
    }


    public static Node prev(Node node, boolean leaf) {
        if(!leaf) {
            return prev(node);
        } else if(node != null) {
            while(node.previousSibling() == null) {
                Node parent = node.parent();
                if(parent == null) {
                    return null;
                }
                node = parent;
            }
            node = node.previousSibling();
            while(!functional.html.is.leaf(node)) {
                node = functional.html.back(node);
            }
            return node;
        }
        throw new RuntimeException("");
    }



    public static Node next(Node node, boolean leaf) {
        if(!leaf) {
            return functional.html.next(node);
        } else if(node != null) {
            while(node.nextSibling() == null) {
                Node parent = node.parent();
                if(parent == null) {
                    return null;
                }
                node = parent;
            }
            node = node.nextSibling();
            while(!functional.html.is.leaf(node)) {
                node = functional.html.front(node);
            }
            return node;
        }
        throw new RuntimeException("");
    }

    public static class to {
        public static Style style(Attr o) {
            if(o instanceof Style){
                return (Style) o;
            }
            return functional.string.equal(o.category(), "style") ? functional.html.to.style(o.value()) : null;
        }
        public static Style style(String v){
            if(!functional.string.empty(v)){
                String[] strings = v.split(";");
                Style style = new Style();
                for(String s : strings) {
                    String[] pair = s.split(":", 2);
                    if(pair.length == 2) {
                        style.put(pair[0].trim(), pair[1].trim());
                    } else {
                        throw new RuntimeException("");
                    }
                }
                return style;
            }
            return null;
        }

        public static String string(Attr attr) {
            return attr.str();
        }

        public static String html(Mark mark) {
            String tag = functional.string.empty(mark.tag()) ? "span" : mark.tag();
            StringBuilder builder = new StringBuilder();
            List<Attr> attrs = mark.attrs();
            if(attrs != null) {
                for(Attr attr : attrs) {
                    builder.append(" ");
                    builder.append(attr.str());

                }
            }
            return String.format(Locale.getDefault(), "<%s%s></%s>", tag, builder.toString(), tag);
        }

        public static String html(Mark mark, Node node) {
            String tag = functional.string.empty(mark.tag()) ? "span" : mark.tag();
            StringBuilder builder = new StringBuilder();
            List<Attr> attrs = mark.attrs();
            for(Attr attr : attrs) {
                builder.append(attr.str());
                builder.append(" ");
            }
            builder.delete(builder.length() -1, builder.length());
            return String.format(Locale.getDefault(), "<%s %s>%s</%s>", tag, builder.toString(), node != null ? node.outerHtml() : "" ,tag);
        }

        public static String html(Mark mark, String text) {
            String tag = functional.string.empty(mark.tag()) ? "span" : mark.tag();
            StringBuilder builder = new StringBuilder();
            List<Attr> attrs = mark.attrs();
            for(Attr attr : attrs) {
                builder.append(attr.str());
                builder.append(" ");
            }
            builder.delete(builder.length() -1, builder.length());
            return String.format(Locale.getDefault(), "<%s %s>%s</%s>", tag, builder.toString(), text != null ? text : "" ,tag);
        }

        public static String string(Document document) { return document != null ? document.outerHtml() : null; }
        public static String string(Node node) { return node != null ? node.outerHtml() : null; }
        public static String string(List<Node> nodes){
            if(nodes != null) {
                StringBuilder builder = new StringBuilder();
                for(Node node : nodes) {
                    builder.append(node.outerHtml());
                }
                return builder.toString();
            }
            return null;
        }
        public static String string(TextNode node) {
            if(node != null) {
                String s = node.outerHtml();
                s = s.replace("&nbsp;", "\u00A0");
                s = s.replace(" ", "\u00A0");
                return s;
            }
            return null;
        }

        public static String html(List<Node> nodes){
            if(nodes != null) {
                StringBuilder builder = new StringBuilder();
                for(Node node : nodes) {
                    if(node != null) {
                        builder.append(node.outerHtml());
                    }
                }
                return builder.toString();
            }
            return "";
        }

        public static String html(Node n) { return n != null ? n.outerHtml() : null; }

        public static String text(TextNode node) {
            if(node != null) {
                String s = node.outerHtml();
                s = s.replace("&nbsp;", "\u00A0");
                s = s.replace("&amp;", "&");
                s = s.replace("&gt;", "<");
                s = s.replace("&lt;", ">");
                return s;
            }
            return "";
        }

        public static String text(Node node){
            StringBuilder builder = new StringBuilder();
            traverse(node, (start, end, depth, n) -> {
                if(functional.html.is.leaf(n)) {
                    if(n instanceof TextNode) {
                        builder.append(functional.html.to.text((TextNode) n));
                    } else if(functional.html.equal(n, "br")) {
                        builder.append(" ");
                    }
                }
                return true;
            });
            return builder.toString();

        }
    }

    public static Node from(Mark mark, List<Node> children) {
        Node node = functional.html.from(mark);
        if(node instanceof Element) {
            Element element = (Element) node;
            ArrayList<Node> nodes = new ArrayList<>(children);
            for(Node child : nodes) {
                element.appendChild(child);
            }
            return node;
        } else {
            throw new RuntimeException("");
        }
    }

    public static Node from(Mark mark, Node child) {
        Node node = functional.html.from(mark);
        if(node instanceof Element) {
            Element element = (Element) node;
            if(child != null) {
                element.appendChild(child);
            }
            return node;
        } else {
            throw new RuntimeException("");
        }
    }

    public static Node from(Mark mark) {
        // todo: validate mark.tag() ... tag name
        String tag = (mark.tag() == null ? "span" : mark.tag());
        if(!functional.html.valid.tag(tag)) {
            throw new RuntimeException("");
        }
        Document document = Jsoup.parse(functional.html.to.html(mark));
        return functional.list.get(functional.html.children(document.body()), 0);
    }

    public static Document from(Node n) {
        Document document = Jsoup.parse(n.outerHtml());
        Document.OutputSettings settings = document.outputSettings();
        settings.prettyPrint(false);
        document.outputSettings(settings);
        return document;
    }

    public static Document from(String html) {
        Document document = Jsoup.parse(html);
        Document.OutputSettings settings = document.outputSettings();
        settings.prettyPrint(false);
        document.outputSettings(settings);
        return document;
    }

    public static boolean print(int start, int end, int depth, Node node) {
        System.out.println(functional.json.from(functional.map.create(functional.pair.create("start", start),
                functional.pair.create("end", end),
                functional.pair.create("depth", depth),
                functional.pair.create("node", node))));
        return true;
    }

    public static void print(Document document) {
        System.out.println(functional.html.to.string(document));
        System.out.println(functional.html.to.string(document.body()));
        System.out.println(functional.html.to.string(functional.html.children(document.body())));
    }

    public static Node front(Node node){ return node != null ? functional.list.front(node.childNodes()) : null; }
    public static Node front(Node node, boolean leaf) {
        if(!leaf) {
            return functional.html.front(node);
        } else {
            while(node != null  && !functional.html.is.leaf(node)) {
                node = functional.list.front(node.childNodes());
            }
            return node;
        }
    }
    public static Node back(Node node){ return node != null ? functional.list.back(node.childNodes()) : null; }
    public static Node back(Node node, boolean leaf) {
        if(!leaf){
            return back(node);
        } else {
            while(node != null && !functional.html.is.leaf(node)) {
                node = functional.list.back(node.childNodes());
            }
            return node;
        }
    }

    public static List<Node> children(Node node){ return node != null ? node.childNodes() : null; }

    public static List<Node> children(Node node, boolean clone){ return node != null ? (clone ? node.childNodesCopy() : node.childNodes()) : null; }

    public static boolean equal(Node n, String name) { return functional.string.equal(n.nodeName(), name); }

    public static boolean equal(Node x, Node y) { return x == y; }

    public static boolean equal(Style x, Style y) {
        return x == y || (x != null && x.equals(y));
    }

    public static boolean equal(Node x, Attr attr) {
        if(x != null) {
            if(attr != null){
                if(functional.string.equal(attr.category(), "style")) {
                    Style style = functional.html.to.style(x.attr("style"));
                    Style y = functional.html.to.style(attr);
                    return functional.html.equal(style, y);
                } else {
                    String v = x.attr(attr.category());
                    return functional.string.equal(v, attr.value());
                }
            }
        }
        return false;
    }

    public static boolean equal(Node x, List<Attr> attrs) {
        if(x != null) {
            if(attrs != null) {
                for(Attr attr : attrs) {
                    if(!functional.html.equal(x, attr)) {
                        return false;
                    }
                }
                return true;
            }
        }
        return false;
    }

    public static boolean equal(Node x, Mark mark) {
        if(x != null) {
            if(mark.tag() != null){
                if(!functional.list.empty(mark.attrs())) {
                    return functional.html.equal(x, mark.tag()) && functional.html.equal(x, mark.attrs());
                } else {
                    return functional.html.equal(x, mark.tag());
                }
            } else {
                return functional.html.equal(x, mark.attrs());
            }
        }
        return false;
    }

    public static boolean empty(List<Node> nodes) { return nodes == null || nodes.size() == 0; }

    public static int distance(Node parent, Node node) {
        int total = 0;
        if(parent != null) {
            List<Node> nodes = parent.childNodes();
            for(Node n : nodes) {
                if(n != node) {
                    total += length(n);
                    continue;
                }
                return total;
            }
        }
        throw new RuntimeException("");
    }

    public static void remove(List<Node> nodes, boolean empty) {
        if(empty) {
            if(nodes != null) {
                ArrayList<Node> list = new ArrayList<>(nodes);
                for(Node node : list) {
                    if(functional.html.length(node) == 0) {
                        functional.html.remove(node);
                    }
                }
            }
        } else {
            remove(nodes);
        }
    }

    public static Node remove(Node node, boolean adjust) {
        Node next = null;
        if(node != null) {
            next = functional.html.next(node, true);
            if(adjust) {
                while(!functional.html.is.root(node.parent()) && functional.list.size(functional.html.children(node.parent())) == 1) {
                    node = node.parent();
                }
            }
            try {
                node.remove();
            } catch(IllegalArgumentException e){
                functional.exception.on(e);
            }
        }
        return next;
    }

    public static Node remove(Node node) {
        Node next = null;
        if(node != null) {
            try {
                next = functional.html.next(node, true);
                node.remove();
            } catch(IllegalArgumentException e){
                functional.exception.on(e);
            }
        }
        return next;
    }

    public static void remove(List<Node> nodes) {
        if(nodes != null) {
            List<Node> list = new ArrayList<>(nodes);
            for(Node node : list) {
                functional.html.remove(node);
            }
        }
    }

    public static void after(Node basis, Node node) {
        if(basis != null && node != null) {
            basis.after(node);
        }
    }

    public static void before(Node basis, Node node) {
        if(basis != null && node != null) {
            basis.before(node);
        }
    }

    public static void append(Element parent, Node node) {
        if(parent != null && node != null) {
            parent.appendChild(node);
        }
    }

    public static void append(Element parent, List<Node> nodes) {
        if(parent != null && nodes != null){
            ArrayList<Node> list = new ArrayList<>(nodes);
            for(Node node : list) {
                functional.html.append(parent, node);
            }
        }
    }

    public static void prepend(Element parent, Node node) {
        if(parent != null && node != null) {
            parent.prependChild(node);
        }
    }

    public static void prepend(Element parent, List<Node> nodes) {
        if(parent != null && nodes != null){
            ArrayList<Node> list = new ArrayList<>(nodes);
            for(int i = list.size() - 1; i >= 0; i--) {
                functional.html.prepend(parent, list.get(i));
            }
        }
    }

    public static int length(TextNode node) {
        String s = functional.html.to.string(node);
        return s != null ? s.length() : 0;
    }

    public static int length(Node node) {
        Single<Integer> single = new Single<>(0);
        if(node != null) {
            Node current = node;
            do {
                if(functional.html.is.leaf(current)) {
                    if(current instanceof TextNode){
                        single.first(single.first() + length((TextNode) current));
                    } else if(functional.html.equal(current, "br")) {
                        single.first(single.first() + 1);
                    }
                }
                if(functional.html.has.children(current)) {
                    current = functional.html.front(current);
                } else {
                    if(current != node) {
                        while(current.nextSibling() == null) {
                            current = current.parent();
                            if(current == node) {
                                return single.first();
                            }
                        }
                        current = current.nextSibling();
                    }
                }
            } while(current != null && current != node);
        }
        return single.first();
    }

    public static int depth(Node n){
        int depth = 0;
        while(n != null){
            depth += 1;
            n = n.parent();
        }
        return depth;
    }

    public static List<Node> merge(Node first, List<Node> second) {
        Document document = Jsoup.parse("");
        Element body = document.body();
        if(first != null) {
            body.appendChild(first);
        }
        if(second != null) {
            ArrayList<Node> children = new ArrayList<>(second);
            for(Node node : children) {
                body.appendChild(node);
            }
        }
        return body.childNodes();
    }

    public static List<Node> merge(List<Node> first, Node second) {
        Document document = Jsoup.parse("");
        Element body = document.body();
        if(first != null) {
            ArrayList<Node> children = new ArrayList<>(first);
            for(Node node : children) {
                body.appendChild(node);
            }
        }
        if(second != null) {
            body.appendChild(second);
        }
        return body.childNodes();
    }

    public static List<Node> merge(Node first, List<Node> second, Node third) {
        Document document = Jsoup.parse("");
        Element body = document.body();
        if(first != null) {
            body.appendChild(first);
        }
        if(second != null) {
            ArrayList<Node> children = new ArrayList<>(second);
            for(Node node : children) {
                body.appendChild(node);
            }
        }
        if(third != null) {
            body.appendChild(third);
        }
        return body.childNodes();
    }

    public static Element clone(Element node, boolean only) {
        if(node != null) {
            Element o = node.clone();
            if(only) {
                remove(o.childNodes());
            }
            return o;
        }
        return null;
    }

    public static Node clone(Node node, boolean only) {
        if(node != null) {
            Node o = node.clone();
            if(only) {
                remove(o.childNodes());
            }
            return o;
        }
        return null;
    }

    public static Node clone(Node node){ return node != null ? node.clone() : null; }
    public static Element clone(Element element){ return element != null ? element.clone() : null; }
    public static Document clone(Document document){ return document != null ? document.clone() : null; }

    public static List<Node> clone(List<Node> nodes) {
        if(nodes != null) {
            LinkedList<Node> list = new LinkedList<>();
            for(Node node : nodes) {
                list.add(node.clone());
            }
            return list;
        }
        return null;
    }

    public static Node clone(Node original, Node begin, Node until, Node node) {
        if(original instanceof Element) {
            if(begin != null) {
                Node current = begin;
                Node destination = null;
                LinkedList<Node> nodes = new LinkedList<>();
                nodes.add(node);
                while(current != null && current != until && current != original) {
                    if(current.nextSibling() != null) {
                        nodes.add(functional.html.clone(current = current.nextSibling()));
                    } else {
                        current = current.parent();
                        destination = functional.html.clone(current, true);
                        functional.html.append((Element) destination, nodes);
                        nodes.clear();
                        nodes.add(destination);
                    }
                }
                if(destination != null) {
                    functional.html.remove(destination.childNodes(), true);
                }
                return destination;
            } else {
                Node current = original;
                Node destination = functional.html.clone(original.clone(), true);
                Node n = destination;
                Element parent = null;
                do {
                    if(functional.html.has.children(current)) {
                        current = functional.html.front(current);
                        if(current != null && current != until && current != original) {
                            if(parent == null) {
                                parent = (Element) destination;
                            } else if(n instanceof Element) {
                                parent = (Element) n;
                            }
                            parent.appendChild(functional.html.clone(current, true));
                            n = functional.html.back(parent);
                        } else if(node != null && functional.html.length(node) > 0) {
                            if(parent == null) {
                                parent = (Element) destination;
                            } else if(n instanceof Element) {
                                parent = (Element) n;
                            }
                            parent.appendChild(node);
                        }
                    } else if(current != until && current != original) {
                        if(current.nextSibling() != null) {
                            current = current.nextSibling();
                            if(current != null && current != until && current != original) {
                                n.after(functional.html.clone(current, true));
                                n = (n.nextSibling()==null ? n : n.nextSibling());
                            } else if(node != null && functional.html.length(node) > 0) {
                                n.after(node);
                            }
                        } else {
                            current = current.parent();
                            n = parent;
                            parent = parent.parent();
                            while(current != null && current != until && current != original) {
                                if(current.nextSibling() == null) {
                                    current = current.parent();
                                    n = parent;
                                    parent = parent.parent();
                                    continue;
                                }
                                current = current.nextSibling();
                                break;
                            }
                            if(current == until || current == original) {
                                if(parent == null) {
                                    parent = (Element) destination;
                                } else if(n instanceof Element) {
                                    parent = (Element) n;
                                }
                                parent.appendChild(node);
                            }
//
//
//                            while(current.nextSibling() != null) {
//                                current = current.nextSibling();
//                            }
//
//                            while(current != null && current != until && current != original) {
//                                while(current.nextSibling() != null) {
//                                    current = current.nextSibling();
//                                    if(current != until && current != original) {
//                                        if(!functional.html.has.child(current, until)) {
//                                            parent.appendChild(n = functional.html.clone(current));
//                                            continue;
//                                        }
//                                        parent.appendChild(n = functional.html.clone(current, true));
//                                        break;
//                                    } else if(node != null && functional.html.length(node) > 0) {
//                                        parent.appendChild(node);
//                                    }
//                                    break;
//                                }
//                                if(!functional.html.has.child(current, until)) {
//                                    if(current != until && current != original) {
//                                        current = current.parent();
//                                        n = parent;
//                                        parent = parent.parent();
//                                        if(current == until || current == original) {
//                                            if(parent != null){
//                                                parent.appendChild(node);
//                                            } else {
//                                                Node back = functional.html.back(n, true);
//                                                if(back != null) {
//                                                    back.after(node);
//                                                } else {
//                                                    throw new RuntimeException("");
//                                                }
//                                            }
//                                        }
//                                    }
//                                }
//                            }
                        }
                    }
                } while(current != null && current != until && current != original);
                functional.html.remove(destination.childNodes(), true);
                return destination;
            }
        } else {
            return node;
        }
    }

    public static void traverse(Node node, visitor visitor) {
        if(node != null) {
            if(visitor != null) {
                Node current = node;
                int start = 0;
                int end = length(node);
                int depth = 0;
                do {
                    if(visitor.on(start, end, depth, current)) {
                        if(functional.html.has.children(current)) {
                            current = functional.html.front(current);
                            end = start + length(current);
                        } else {
                            if(current != node) {
                                while(current.nextSibling() == null) {
                                    Node parent = current.parent();
                                    if(parent == node) {
                                        return;
                                    }
                                    int distance = functional.html.distance(parent, current);
                                    current = parent;
                                    start -= distance;
                                    end = start + length(current);
                                }
                                start = end;
                                current = current.nextSibling();
                                end = start + length(current);
                            }
                        }
                        continue;
                    }
                    break;
                } while(current != null && current != node);
            } else {
                throw new RuntimeException("");
            }
        }
    }

    public static Pair<Node, Integer> find(Node node, int index) {
        Pair<Node, Integer> found = new Pair<>();
        traverse(node, (start, end, depth, n) -> {
            if(start <= index && index < end && functional.html.is.leaf(n)) {
                found.set(n, start);
                return false;
            }
            return true;
        });
        return found;
    }

    public static Pair<Node, Integer> find(Node node, int from, int to) {
        Pair<Node, Integer> found = new Pair<>();
        traverse(node, (start, end, depth, n) -> {
            if(start <= from && from < end && functional.html.is.leaf(n)) {
                if(n != node) {
                    while(end < to) {
                        Node parent = n.parent();
                        int distance = functional.html.distance(parent, n);
                        if(parent != node) {
                            start -= distance;
                            end = start + functional.html.length(parent);
                            n = parent;
                            continue;
                        }
                        break;
                    }
                    if(end < to) {
                        found.set(node, 0);
                        return false;
                    }
                }
                found.set(n, start);
                return false;
            }
            return true;
        });
        return found;
    }

    public static List<Node> split(Node original, int index) {
        if(original != null) {
            if(index == 0) {
                return functional.list.create(null, original.clone());
            } else {
                int length = functional.html.length(original);
                if(length < index) {
                    throw new RuntimeException("");
                } else if(length == index) {
                    return functional.list.create(original.clone(), (Node) null);
                } else {
                    Node current = original.clone();
                    Pair<Node, Integer> found = functional.html.find(current, index);
                    if(!found.empty()) {
                        if(found.first() instanceof TextNode){
                            String s = functional.html.to.string((TextNode) found.first());
                            Node front = functional.html.clone(current, null, found.first(), new TextNode(s.substring(0, index - found.second())));
                            Node back = functional.html.clone(current, found.first(), null, new TextNode(s.substring(index - found.second())));
                            return functional.list.create(front, back);
                        } else if(functional.html.equal(found.first(), "br")) {
                            Node front = functional.html.clone(current, null, found.first(), null);
                            Node back = functional.html.clone(current, found.first(), null, functional.html.clone(found.first(), true));
                            return functional.list.create(front, back);
                        } else {
                            throw new RuntimeException("");
                        }
                    }
                    return functional.list.create(null, (Node) null);
                }
            }
        } else {
            return functional.list.create(null, (Node) null);
        }
    }

    public static List<Node> split(Node node, int from, int to) {
        if(to <= from) {
            throw new RuntimeException("");
        }
        List<Node> first = functional.html.split(node, from);
        if(first != null) {
            if(first.size() == 2) {
                if(first.get(1) != null) {
                    List<Node> second = functional.html.split(first.get(1), to - from);
                    return functional.list.create(first.get(0), second.get(0), second.get(1));
                } else {
                    return functional.list.add(first, null);
                }
            } else {
                throw new RuntimeException("");
            }
        }
        return functional.list.create(null, null, null);
    }

    public static void replace(Node original, Node previous, Node parent, Node node) {
        if(original != null) {
            if(previous != null) {
                original.remove();
                previous.after(node);
            } else if(parent != null) {
                original.remove();
                functional.html.prepend((Element) parent, node);
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static void replace(Node original, Node previous, Node parent, List<Node> nodes) {
        if(original != null) {
            if(previous != null) {
                original.remove();
                previous.after(functional.html.to.html(nodes));
            } else if(parent != null) {
                original.remove();
                functional.html.prepend((Element) parent, nodes);
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static List<Node> replace(Node original, Node replacement) {
        if(original != null) {
            if(replacement instanceof Element) {
                if(functional.html.equal(replacement, "br")) {
                    if(functional.html.has.children(original)) {
                        throw new RuntimeException("");
                    }
                    return functional.list.create(replacement);
                } else {
                    functional.html.append((Element) replacement, original.childNodesCopy());
                    return functional.list.create(replacement);
                }
            } else if(replacement == null) {
                return original.childNodesCopy();
            } else {
                if(functional.html.has.children(original)) {
                    throw new RuntimeException("");
                }
                return functional.list.create(replacement);
            }
        }
        return null;
    }

    public static void mark(Node node, Mark mark, int from, int to) {
        Pair<Node, Integer> found = functional.html.find(node, from, to);
        if(found != null) {
            if(!found.empty()) {
                Node current = found.first();
                List<Node> nodes = functional.html.split(current, from - found.second(), to - found.second());
                if(nodes != null) {
                    if(nodes.size() == 3) {
                        if(current.parent() == null || functional.html.equal(current.parent(), "body")) {
                            nodes.set(1, functional.html.from(mark, functional.html.children(nodes.get(1))));
                            functional.html.remove(node.childNodes());
                            functional.html.append((Element) node, functional.html.children(nodes.get(0)));
                            functional.html.append((Element) node, nodes.get(1));
                            functional.html.append((Element) node, functional.html.children(nodes.get(2)));
                        } else {
                            nodes.set(1, functional.html.from(mark, nodes.get(1)));
                            if(current.previousSibling() != null) {
                                Node previous = current.previousSibling();
                                functional.html.remove(current);
                                previous.after(functional.html.to.html(nodes));
                            } else if(current.parent() instanceof Element) {
                                Element parent = (Element) current.parent();
                                functional.html.remove(current);
                                functional.html.prepend(parent, nodes);
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
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static void unmark(Node node, Mark mark, int from, int to) {
        Pair<Node, Integer> found = functional.html.find(node, from, to);
        if(functional.pair.exist(found)) {
            Node current = found.first();
            int distance = 0;
            while(current != null && !functional.html.equal(current, "body")) {
                if(!functional.html.equal(current, mark)) {
                    distance += (current.parent() != null ? functional.html.distance(current.parent(), current) : 0);
                    current = current.parent();
                    continue;
                }
                found.set(current, found.second() - distance);
                break;
            }
            ArrayList<Triple<Node, Integer, Integer>> nodes = new ArrayList<>();
            traverse(found.first(), (start, end, depth, n) -> {
                if(n != found.first() && functional.html.equal(n, mark)) {
                    start += found.second();
                    end += found.second();
                    if((start <= from && from < end) || (start < to && to <= end)) {
                        nodes.add(functional.tuple.triple.create(n, start, end));
                    }
                }
                return true;
            });
            if(functional.html.equal(found.first(), mark)) {
                nodes.add(functional.tuple.triple.create(found.first(), found.second(), found.second() + functional.html.length(found.first())));
            }
            if(functional.list.exist(nodes)) {
                for(Triple<Node, Integer, Integer> n : nodes) {
                    int start = n.second();
                    int end = n.third();
                    if(from <= start) {
                        if(end <= to) {
                            // System.out.println(String.format(Locale.getDefault(), "= [%s][replace] %02d:%02d/%02d:%02d", functional.string.v(mark.tag()), from, to, start, end));
                            current = n.first();
                            functional.html.replace(n.first(), functional.html.prev(n.first()), functional.html.parent(n.first()), current.childNodesCopy());
                        } else {
                            // System.out.println(String.format(Locale.getDefault(), "= [%s][split(2)/unmark(front)] %02d:%02d/%02d:%02d", functional.string.v(mark.tag()), from, to, start, end));
                            List<Node> children = functional.html.split(n.first(), to - start);
                            if(children.size() == 2) {
                                List<Node> replacements = functional.html.merge(functional.html.children(children.get(0), true), children.get(1));
                                functional.html.replace(n.first(), functional.html.prev(n.first()), functional.html.parent(n.first()), replacements);
                            } else {
                                throw new RuntimeException("");
                            }
                        }
                    } else {
                        if(end <= to) {
                            // System.out.println(String.format(Locale.getDefault(), "= [%s][split(2)/unmark(back)] %02d:%02d/%02d:%02d", functional.string.v(mark.tag()), from, to, start, end));
                            List<Node> children = functional.html.split(n.first(), from - start);
                            if(children.size() == 2) {
                                List<Node> replacements = functional.html.merge(children.get(0), functional.html.children(children.get(1), true));
                                functional.html.replace(n.first(), functional.html.prev(n.first()), functional.html.parent(n.first()), replacements);
                            } else {
                                throw new RuntimeException("");
                            }
                        } else {
                            // System.out.println(String.format(Locale.getDefault(), "= [%s][split(3)/unmark(middle)] %02d:%02d/%02d:%02d", functional.string.v(mark.tag()), from, to, start, end));
                            List<Node> children = functional.html.split(n.first(), from - start, to - start);
                            if(children.size() == 3) {
                                List<Node> replacements = functional.html.merge(children.get(0), functional.html.children(children.get(1), true), children.get(2));
                                functional.html.replace(n.first(), functional.html.prev(n.first()), functional.html.parent(n.first()), replacements);
                            } else {
                                throw new RuntimeException("");
                            }
                        }
                    }
                }
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static String text(String v) {
        if(v != null) {
            v = v.replace(" ", "\u00A0");
            // TODO: SPECIAL CHARACTER
            return v;
        }
        return "";
    }

    public static String str(String v) {
        if(v != null) {
            v = v.replace(" ", "\u00A0");
            v = v.replace("&nbsp;", "\u00A0");
            v = v.replace("&amp;", "&");
            v = v.replace("&gt;", "<");
            v = v.replace("&lt;", ">");
        }
        return v;
    }

    public static void set(TextNode node, String v) {
        if(node != null) {
            node.text(functional.html.str(v));
        }
    }

    public static void insert(Node node, int index, String text) {
        if(node != null) {
            if(index - 1 == functional.html.length(node)) {
                Node front = functional.html.front(node, true);
                if(front instanceof Element) {
                    Element element = (Element) front;
                    element.appendChild(new TextNode(functional.html.text(text)));
                    System.out.println(element);
                } else if(front == null && node instanceof Element) {
                    Element element = (Element) node;
                    element.prependChild(new TextNode(functional.html.text(text)));
                } else {
                    throw new RuntimeException("");
                }
            } else {
                Pair<Node, Integer> found = functional.html.find(node, index);
                if(functional.pair.exist(found)) {
                    if(found.first() instanceof TextNode) {
                        List<String> strings = functional.string.split(functional.html.to.text(found.first()), index - found.second());
                        if(functional.list.size(strings) == 2) {
                            String s = functional.string.merge(strings.get(0), text, strings.get(1));
                            functional.html.set((TextNode) found.first(), s);
                        } else {
                            throw new RuntimeException("");
                        }
                    } else if(functional.html.equal(found.first(), "br")) {
                        Node current = found.first();
                        current.before(new TextNode(functional.html.text(text)));
                    } else {
                        throw new RuntimeException("");
                    }
                } else if(functional.html.length(node) == index) {
                    Node current = functional.html.back(node, true);
                    if(current != null) {
                        if(current == node) {
                            Element element = (Element) current;
                            element.prependChild(new TextNode(functional.html.text(text)));
                        } else {
                            current.after(new TextNode(functional.html.text(text)));
                        }

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

    public static void insert(Node node, int index, Node n) {
        if(node != null) {
            if(index - 1 == functional.html.length(node)) {
                Node front = functional.html.front(node, true);
                if(front instanceof Element) {
                    Element element = (Element) front;
                    element.appendChild(n);
                } else if(front == null && node instanceof Element) {
                    Element element = (Element) node;
                    element.prependChild(n);
                } else {
                    throw new RuntimeException("");
                }
            } else {
                Pair<Node, Integer> found = functional.html.find(node, index);
                if(functional.pair.exist(found)) {
                    if(found.first() instanceof TextNode) {
                        List<String> strings = functional.string.split(functional.html.to.text(found.first()), index - found.second());
                        if(functional.list.size(strings) == 2) {
                            functional.html.set((TextNode) found.first(), strings.get(0));
                            Node current = found.first();
                            current.after(n);
                            n.after(new TextNode(strings.get(1)));
                        } else {
                            throw new RuntimeException("");
                        }
                    } else if(functional.html.equal(found.first(), "br")) {
                        Node current = found.first();
                        current.before(n);
                    } else {
                        throw new RuntimeException("");
                    }
                } else if(functional.html.length(node) == index) {
                    Node current = functional.html.back(node, true);
                    if(current == node) {
                        Element element = (Element) current;
                        element.prependChild(n);
                    } else {
                        current.after(n);
                    }
                } else {
                    throw new RuntimeException("");
                }
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static void remove(Node node, int index) {
        Pair<Node, Integer> found = functional.html.find(node, index);
        if(functional.pair.exist(found)) {
            if(found.first() instanceof TextNode) {
                String s = functional.html.to.text(found.first());
                index -= found.second();
                s = s.substring(0, index) + (index + 1 <= s.length() ? s.substring(index + 1) : "");
                functional.html.set((TextNode) found.first(), s);
            } else if(functional.html.equal(found.first(), "br")) {
                functional.html.remove(found.first(), true);
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
    }

    public static Node remove(TextNode node, int from, int to) {
        Node next = null;
        if(node != null) {
            next = functional.html.next(node, true);
            String s = functional.html.to.text(node);
            s = s.substring(0, from) + s.substring(to);
            node.text(s);
        }
        return next;
    }

    public static Node remove(TextNode node, int until) {
        Node next = null;
        if(node != null) {
            next = functional.html.next(node, true);
            String s = functional.html.to.text(node);
            s = s.substring(until);
            node.text(s);
        }
        return next;
    }

    public static void remove(Node node, int from, int to) {
        Pair<Node, Integer> found = functional.html.find(node, from, to);
        if(functional.pair.exist(found)) {
            if(found.first() instanceof TextNode) {
                String s = functional.html.to.text(found.first());
                s = s.substring(0, from - found.second()) + s.substring(to - found.second());
                functional.html.set((TextNode) found.first(), s);
            } else if(functional.html.equal(found.first(), "br")) {
                functional.html.remove(found.first(), true);
            } else {
                int index = found.second();
                Node current = functional.html.front(found.first(), true);
                while(current != null && index <= to) {
                    int length = functional.html.length(current);
                    if(from <= index) {
                        if(index + length <= to) {
                            current = functional.html.remove(current, true);
                        } else if(index < to) {
                            if(current instanceof TextNode) {
                                current = functional.html.remove((TextNode) current, to - index);
                            } else if(length == 0) {
                                current = functional.html.remove(current, true);
                            } else {
                                throw new RuntimeException("");
                            }
                        } else {
                            current = functional.html.next(current, true);
                        }
                    } else if(from < index + length) {
                        if(index + length <= to) {
                            if(current instanceof TextNode) {
                                current = functional.html.remove((TextNode) current, from - index, length);
                            } else if(length == 0) {
                                current = functional.html.remove(current, true);
                            } else {
                                throw new RuntimeException("");
                            }
                        } else {
                            if(current instanceof TextNode) {
                                current = functional.html.remove((TextNode) current, from - index, to - index);
                            } else if(length == 0) {
                                current = functional.html.remove(current, true);
                            } else {
                                throw new RuntimeException("");
                            }
                        }
                    } else {
                        current = functional.html.next(current, true);
                    }
                    index += length;
                }
            }
        }
    }

    public static Node enter(Node node, int index) {
        throw new RuntimeException("");
    }
    private static void checkSplitByRange() {
        Document document = functional.html.from("<p id=\"nd-50717836\"><br /><a href=\"https://post.naver.com/viewer/postView.nhn?volumeNo=17207988&amp;memberNo=6132524\"><span contenteditable=\"false\" class=\"link-deco\">https://post.naver.com/viewer/<br />postView.nhn?volumeNo=17207988&amp;memberNo=6132524</span></a> <br /></p>");
        Node node = functional.list.get(functional.html.children(document.body()), 0);
        if(node != null){
            int total = functional.html.length(node);
            System.out.println("p: " + node.outerHtml());
            System.out.println("total: " + total);
            for(int i = 0; i < total / 4; i++) {
                for(int j = i + 1; j <= total; j++) {
                    System.out.println("functional.html.split(node, " + i + ", " + j + ")");
                    List<Node> nodes = functional.html.split(node, i, j);
                    if(nodes != null) {
                        System.out.println(String.format(Locale.getDefault(), "text[0]: \n%s\n%s\n%s", functional.html.to.html(nodes.get(0)),
                                functional.html.to.html(nodes.get(1)),
                                functional.html.to.html(nodes.get(2))));

                    } else {
                        System.out.println("node is not split");
                    }
                }
            }
        } else {
            System.out.println("p: " + null);
        }
    }

    private static void checkSplitByIndex() {
        Document document = functional.html.from("<p id=\"nd-50717836\"><br /><a href=\"https://post.naver.com/viewer/postView.nhn?volumeNo=17207988&amp;memberNo=6132524\"><span contenteditable=\"false\" class=\"link-deco\">https://post.naver.com/viewer/<br />postView.nhn?volumeNo=17207988&amp;memberNo=6132524</span></a> <br /></p>");
        Node node = functional.list.get(functional.html.children(document.body()), 0);
        if(node != null){
            int total = functional.html.length(node);
            System.out.println("p: " + node.outerHtml());
            System.out.println("total: " + total);
            for(int i = 0; i <= total; i++) {
                System.out.println("functional.html.split(node, " + i + ")");
                List<Node> nodes = functional.html.split(node, i);
                if(nodes != null) {
                    // System.out.println("node[" + 0 + "]: " + functional.html.to.html(nodes.get(0)));
                    // System.out.println("node[" + 1 + "]: " + functional.html.to.html(nodes.get(1)));
                    System.out.println("text[" + 0 + "]: [" + functional.html.to.text(nodes.get(0)) + ":" + functional.string.fill(" ", functional.html.length(nodes.get(1))) + "]");
                    System.out.println("text[" + 1 + "]: [" + functional.string.fill(" ", functional.html.length(nodes.get(0))) + ":" + functional.html.to.text(nodes.get(1)) + "]");

                } else {
                    System.out.println("node is not split");
                }
            }
        } else {
            System.out.println("p: " + null);
        }
    }

    private static void checkMark(){
        Document document = functional.html.from("<p id=\"nd-50717836\"><br /><a href=\"https://post.naver.com/viewer/postView.nhn?volumeNo=17207988&amp;memberNo=6132524\"><span contenteditable=\"false\" class=\"link-deco\">https://post.naver.com/viewer/<br />postView.nhn?volumeNo=17207988&amp;memberNo=6132524</span></a> <br /></p>");
        Node node = functional.list.get(functional.html.children(document.body()), 0);
        if(node != null) {
            int total = functional.html.length(node);
            Node current;
            for(int i = 0; i < total; i++) {
                for(int j = i + 1; j <= total; j++) {
                    current = node.clone();
                    System.out.println("functional.html.mark(node, " + i + ", " + j +")");
                    functional.html.mark(current, functional.json.to("{\"tag\":\"strong\"}", Mark.class), i, j);
                    System.out.println("current: " + current.outerHtml());
                }
            }
        }
    }
    private static void checkUnmark(Mark mark){
        Document document = functional.html.from("<p id=\"nd-50717836\"><br /><a href=\"https://post.naver.com/viewer/postView.nhn?volumeNo=17207988&amp;memberNo=6132524\"><span contenteditable=\"false\" class=\"link-deco\">https://post.naver.com/viewer/<br />postView.nhn?volumeNo=17207988&amp;memberNo=6132524</span></a> <br /></p>");
        Node node = functional.list.get(functional.html.children(document.body()), 0);
        if(node != null) {
            int total = functional.html.length(node);
            Node current;
            for(int i = 0; i < total; i++) {
                for(int j = i + 1; j <= total; j++) {
                    current = node.clone();
                    System.out.println("functional.html.unmark(node, " + functional.json.from(mark) + " " + i + ", " + j +")");
                    functional.html.unmark(current, mark, i, j);
                    System.out.println("current: " + current.outerHtml());
                }
            }
            current = node.clone();
            System.out.println("functional.html.unmark(node, " + functional.json.from(mark) + " " + 74 + ", " + 76 +")");
            functional.html.unmark(current, mark, 76, 79);
            System.out.println("current: " + current.outerHtml());
        }
    }

    public static void main(String[] args) {
        functional.json.init(o->{
            o.registerTypeAdapter(Document.class, new GsonDocumentSerializer());
            o.registerTypeAdapter(Element.class, new GsonElementSerializer());
            o.registerTypeAdapter(TextNode.class, new GsonTextNodeSerializer());
        });
        checkUnmark(functional.json.to("{\"tag\":\"a\"}", Mark.class));
        checkUnmark(functional.json.to("{\"tag\":\"span\"}", Mark.class));

    }
}
