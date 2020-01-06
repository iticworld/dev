package hornet.editor.html.server;

import novemberizing.Listener;
import novemberizing.Sync;
import novemberizing.tuple.Triple;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.nodes.TextNode;

import javax.websocket.SendHandler;
import java.util.List;

public abstract class RemoteDocument extends Sync {
    protected String __id;
    protected Document __document;
    protected RemoteCoworkerMap __coworkers = new RemoteCoworkerMap();
    protected RemoteLineMap __lines = new RemoteLineMap();
    protected Long __version;

    public abstract void load();

    public RemoteDocument(String id) {
        __id = id;
        __document = null;
        __version = 0L;
    }

    public Long exec(RemoteDocumentCommand command) {
        switch(command.type()) {
            case "insert": return insert(command);
            case "remove": return remove(command);
            case "replace": return replace(command);
            case "exchange": return exchange(command);
            case "enter": return enter(command);
            case "mark": return mark(command);
            case "unmark": return unmark(command);
            default: throw new RuntimeException("");
        }
    }

    public Long replace(RemoteDocumentCommand command) {
        Document document = functional.html.clone(__document);
        Element element = document.getElementById(command.id());
        if(element != null) {
            Triple<Element, Integer, Integer> found = functional.html.adjust.element(element, command.index());
            if(functional.tuple.exist(found)) {
                functional.html.replace(found.first(), functional.html.adjust.index(element, command.from() - found.second()), functional.html.adjust.index(element, command.to() - found.second()), command.text());
                System.out.println("output: " + element);
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
        __document = document;
        return ++__version;
    }

    public Long exchange(RemoteDocumentCommand command) {
        Document document = functional.html.clone(__document);
        Element front = document.getElementById(command.prev.id());
        if(front == null) {
            front = functional.html.begin(document.body());
        }
        front = (front != null ? front.nextElementSibling() : null);
        Element element = document.getElementById(command.id());
        if(front != null) {
            if(element != null) {
                if(functional.html.adjust.index(element, command.from()) == -1) {
                    functional.html.exchange(front, functional.html.adjust.index(element, command.from()) + 1, functional.html.adjust.index(element, command.to()), element, command.mark(0));
                } else {
                    throw new RuntimeException("");
                }
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
        __document = document;
        return ++__version;
    }

    public Long remove(RemoteDocumentCommand command) {
        Document document = functional.html.clone(__document);
        Element element = document.getElementById(command.id());
        if(element != null) {
            System.out.println("element: " + element);
            Triple<Element, Integer, Integer> found = functional.html.adjust.element(element, command.index());
            if(functional.tuple.exist(found)) {
                functional.html.replace(found.first(), functional.html.adjust.index(element, command.from() - found.second()), functional.html.adjust.index(element, command.to() - found.second()), null);
                System.out.println("output: " + element);
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
        __document = document;
        return ++__version;
    }

    public Long insert(RemoteDocumentCommand command) {
        Document document = functional.html.clone(__document);
        Element element = document.getElementById(command.id());
        if(element != null) {
            System.out.println("element: " + element);
            Triple<Element, Integer, Integer> found = functional.html.adjust.element(element, command.index());
            if(functional.tuple.exist(found)) {
                System.out.println("found.index: " + functional.html.adjust.index(element, command.index() - found.second()));
                System.out.println("found.first: " + found.first());
                System.out.println("found.second: " + found.second());
                System.out.println("found.third: " + command.text());
                System.out.println("text: " + found.third());
                functional.html.insert(found.first(), functional.html.adjust.index(element, command.index() - found.second()), command.text());
                System.out.println("output: " + element);
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
        __document = document;
        return ++__version;
    }

    public Long enter(RemoteDocumentCommand command) {
        Document document = functional.html.clone(__document);
        Element element = document.getElementById(command.id());
        // 맨 첫 라인에서 element 가 NULL일 수 있습니다.
        if(element != null) {
            System.out.println("element: " + element);
            Triple<Element, Integer, Integer> found = functional.html.adjust.element(element, command.index());
            if(functional.tuple.exist(found)) {
                List<Element> elements = functional.html.enter(found.first(), functional.html.adjust.index(element, command.index() - found.second()), command.marks());
                for(Element o : elements) {
                    System.out.println("output: " + o);
                }
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
        __document = document;
        return ++__version;
    }

    public Long mark(RemoteDocumentCommand command) {
        Document document = functional.html.clone(__document);
        Element element = document.getElementById(command.id());
        // 맨 첫 라인에서 element 가 NULL일 수 있습니다.
        if(element != null) {
            System.out.println("element: " + element);
            Triple<Element, Integer, Integer> found = functional.html.adjust.element(element, command.index());
            if(functional.tuple.exist(found)) {
                functional.html.mark(found.first(), functional.html.adjust.index(element, command.from() - found.second()), functional.html.adjust.index(element, command.to() - found.second()), command.mark(0));
                System.out.println("output: " + element);
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
        __document = document;
        return ++__version;
    }

    public Long unmark(RemoteDocumentCommand command) {
        Document document = functional.html.clone(__document);
        Element element = document.getElementById(command.id());
        // 맨 첫 라인에서 element 가 NULL일 수 있습니다.
        if(element != null) {
            System.out.println("element: " + element);
            Triple<Element, Integer, Integer> found = functional.html.adjust.element(element, command.index());
            if(functional.tuple.exist(found)) {
                functional.html.unmark(found.first(), functional.html.adjust.index(element, command.from() - found.second()), functional.html.adjust.index(element, command.to() - found.second()), command.mark(0));
                System.out.println("output: " + element);
            } else {
                throw new RuntimeException("");
            }
        } else {
            throw new RuntimeException("");
        }
        __document = document;
        return ++__version;
    }

    public void get(Listener<RemoteDocument> callback) {
        try {
            lock();
            callback.on(this);
        } catch(Exception e) {
            e.printStackTrace();
        } finally {
            unlock();
        }
    }

    public List<RemoteCoworker> users(){ return __coworkers.list(); }
    public List<RemoteCoworker> join(RemoteCoworker coworker) { return __coworkers.join(coworker); }
    public List<RemoteCoworker> leave(RemoteCoworker coworker) { return __coworkers.leave(coworker); }
    public List<String> own(RemoteCoworker coworker, List<String> prev, List<String> next) {
        return __lines.own(coworker, prev, next);
    }

    public <T> void broadcast(T o, SendHandler handler) {
        if(o != null) {
            __coworkers.broadcast(o, handler);
        }
    }

    public String out() {
        lock();
        Document document = functional.html.clone(__document);
        unlock();
        if(document != null) {
            List<Element> elements = document.select("*");
            for(Element element : elements) {
                if(!functional.html.is.code(element)) {
                    for(TextNode node : element.textNodes()) {
                        String s = node.getWholeText();
                        s = s.replace(" ", "\u00A0");
                        node.text(s);
                    }
                }
            }
            String s = functional.html.to.string(document.body(), true);
            System.out.println(s);
            return s;
        }
        return "";
    }

    public Long version(){ return __version; }
    public String id(){ return __id; }

//    public interface Get { void get(DocumentRemoteRoot document); }


//
//    public Long exec(DocumentRemoteCommand command) {
//        if(command != null) {
//            switch(command.type()){
//                case "insert": return insert(command.id(), command.from(), command.text());
//                case "replace": return replace(command.id(), command.from(), command.to(), command.text(), command.mark());
//                case "remove": return remove(command.id(), command.from(), command.to());
//                case "mark": return mark(command.id(), command.from(), command.to(), command.mark());
//                case "unmark": return unmark(command.id(), command.from(), command.to(), command.mark());
//                case "enter": return enter(command.id(), command.from(), command.to(), command.marks(), command.prev());
//                case "around": return around(command.id(), command.from(), command.to(), command.mark(), command.prev());
//                case "unaround": return unaround(command.id(), command.from(), command.to(), command.prev());
//                default: throw new RuntimeException("");
//            }
//        } else {
//            throw new RuntimeException("");
//        }
//    }
//
//    public void get(Listener<DocumentRemoteRoot> callback) {
//        lock();
//        callback.on(this);
//        unlock();
//    }
//

//

//
//    public Long remove(String id, int from, int to) {
//        try {
//            System.out.println("id: " + id);
//            System.out.println("from: " + from);
//            System.out.println("to: " + to);
//            lock();
//            Document document = functional.html.clone(__document);
//            Element element = document.getElementById(id);
//            if(element != null) {
//                if(functional.html.is.block(element)) {
//                    throw new RuntimeException("");
//                } else {
//                    from = functional.html.index(element, from);
//                    to = functional.html.index(element, to);
//                    int length = functional.html.length(element);
//                    int adjust = functional.html.adjust.length(element.nodeName());
//                    System.out.println("from: " + from);
//                    System.out.println("to: " + to);
//                    System.out.println("length: " + length);
//                    if(from == -1) {
//                        if(from + adjust == to) {
//                            Element prev = element.previousElementSibling();
//                            if(prev != null) {
//                                prev.attr("id", id);
//                                functional.html.append(prev, element.childNodesCopy());
//                                element.remove();
//                                __document = document;
//                                return ++__version;
//                            } else {
//                                throw new RuntimeException("");
//                            }
//                        } else {
//                            throw new RuntimeException("");
//                        }
//                    } else if(from + adjust == to) {
//                        Element next = element.nextElementSibling();
//                        functional.html.append(element, next.childNodesCopy());
//                        next.remove();
//                        __document = document;
//                        return ++__version;
//                    } else if(0 <= from && to <= length - adjust) {
//                        functional.html.replace(element, from, to, null);
//                        __document = document;
//                        return ++__version;
//                    } else if(0 <= from && to == length) {
//                        Element next = element.nextElementSibling();
//                        functional.html.append(element, next.childNodesCopy());
//                        next.remove();
//                        __document = document;
//                        return ++__version;
//                    } else {
//                        functional.html.replace(element, from, to, null);
//                        __document = document;
//                        return ++__version;
//                    }
//                }
//            } else {
//                throw new RuntimeException("element is null");
//            }
//        } catch(Exception e) {
//            System.err.println("id: " + id);
//            System.err.println("from: " + from);
//            System.err.println("to: " + to);
//            throw e;
//        } finally {
//            unlock();
//        }
//    }
//
//    @SuppressWarnings("Duplicates")
//    public Long enter(String id, int from, int to, List<Mark> marks, DocumentRemoteLine prev) {
//        System.out.println("id: " + id);
//        System.out.println("from: " + from);
//        System.out.println("to: " + to);
//        System.out.println("marks.get(0): " + functional.json.from(marks.get(0)));
//        System.out.println("marks.get(1): " + functional.json.from(marks.get(1)));
//        System.out.println("prev: " + functional.json.from(prev));
//        Document document = functional.html.clone(__document);
//        Element element = document.getElementById(id);
//        if(functional.html.is.block(element)) {
//            Triple<Element, Integer, Integer> found = functional.html.adjust.find(element, from);
//            if(functional.tuple.exist(found)) {
//                System.out.println("found: " + found.first());
//                System.out.println("found[start]: " + found.second());
//                element = found.first();
//                from = from - found.second() - 1;
//                to = to - found.second() - 1;
//                System.out.println("from: " + from);
//                System.out.println("to: " + to);
//                int length = functional.html.length(element);
//                int adjust = 0;
//                if(element != null) {
//                    adjust = functional.html.adjust.length(element.nodeName());
//                }
//                System.out.println("element: " + element);
//                System.out.println("length: " + functional.html.length(element));
//                if(element != null) {
//                    if(from == to) {
//                        if(from + adjust == length) {
//                            Element first = functional.html.to.element(marks.get(0), element.childNodesCopy());
//                            Element second = functional.html.to.element(marks.get(1));
//                            functional.html.replace(element, first);
//                            first.after(second);
//                            __document = document;
//                            return ++__version;
//                        } else if(from + adjust < length) {
//                            List<Node> children = functional.html.split(element, from);
//                            Element first = functional.html.to.element(marks.get(0), functional.html.children(children.get(0)));
//                            Element second = functional.html.to.element(marks.get(1), functional.html.children(children.get(1)));
//                            functional.html.replace(element, first);
//                            first.after(second);
//                            __document = document;
//                            return ++__version;
//                        } else {
//                            throw new RuntimeException("");
//                        }
//                    } else {
//                        throw new RuntimeException("");
//                    }
//                } else {
//                    throw new RuntimeException("");
//                }
//            } else {
//                throw new RuntimeException("");
//            }
//        } else {
//            int length = functional.html.length(element);
//            int adjust = 0;
//            if(element != null) {
//                adjust = functional.html.adjust.length(element.nodeName());
//            }
//            System.out.println("element: " + element);
//            System.out.println("length: " + functional.html.length(element));
//            if(element != null) {
//                if(from == to) {
//                    if(from + adjust == length) {
//                        Element first = functional.html.to.element(marks.get(0), element.childNodesCopy());
//                        Element second = functional.html.to.element(marks.get(1));
//                        functional.html.replace(element, first);
//                        first.after(second);
//                        __document = document;
//                        return ++__version;
//                    } else if(from + adjust < length) {
//                        List<Node> children = functional.html.split(element, from);
//                        Element first = functional.html.to.element(marks.get(0), functional.html.children(children.get(0)));
//                        Element second = functional.html.to.element(marks.get(1), functional.html.children(children.get(1)));
//                        functional.html.replace(element, first);
//                        first.after(second);
//                        __document = document;
//                        return ++__version;
//                    } else {
//                        throw new RuntimeException("");
//                    }
//                } else {
//                    throw new RuntimeException("");
//                }
//            } else {
//                throw new RuntimeException("");
//            }
//        }
//    }
//
//    public Long insert(String id, int index, String v) {
//        try {
//            lock();
//            Document document = functional.html.clone(__document);
//            Element element = document.getElementById(id);
//            if(element != null) {
//                index = functional.html.index(element, index);
//                if(index == -1) {
//                    index = 0;
//                }
//                System.out.println("insert");
//                if(functional.html.is.block(element)) {
//                    Triple<Element, Integer, Integer> found = functional.html.adjust.find(element, index);
//                    if(functional.tuple.exist(found)) {
//                        element = found.first();
//                        System.out.println(found.first());
//                        System.out.println(found.second());
//                        System.out.println(index);
//                        index = index - found.second();
//                        System.out.println(index);
//                    } else {
//                        throw new RuntimeException("");
//                    }
//                }
//                System.out.println(element);
//                functional.html.insert(element, index, v);
//                System.out.println(element);
//            } else {
//                throw new RuntimeException("element is null");
//            }
//            __document = document;
//            return ++__version;
//        } catch(Exception e) {
//            System.err.println("id: " + id);
//            System.err.println("from: " + index);
//            System.err.println("v: " + v);
//            throw e;
//        } finally {
//            unlock();
//        }
//    }
//
//    public Long replace(String id, int from, int to, String v, Mark mark) {
//        try {
//            lock();
//            Document document = functional.html.clone(__document);
//            Element element = document.getElementById(id);
//            if(element != null) {
//                from = functional.html.index(element, from);
//                to = functional.html.index(element, to);
//                if(from == -1) {
//                    from += 1;
//                    to += 1;
//                }
//                if(functional.html.is.block(element)) {
//                    Triple<Element, Integer, Integer> found = functional.html.adjust.find(element, from);
//                    if(functional.tuple.exist(found)) {
//                        element = found.first();
//                        from = from - found.second();
//                        to = to - found.second();
//                    } else {
//                        throw new RuntimeException("");
//                    }
//                }
//                System.out.println("replace");
//                System.out.println(element);
//                if(functional.string.empty(v)) {
//                    functional.html.replace(element, from, to, null);
//                    if(!functional.string.equal(mark.id(), element.id())) {
//                        throw new RuntimeException("");
//                    }
//                } else {
//                    functional.html.replace(element, from, to, v);
//                }
//                System.out.println(element);
//            } else {
//                throw new RuntimeException("");
//            }
//            __document = document;
//            return ++__version;
//        } catch(Exception e) {
//            System.out.println("id: " + id);
//            System.out.println("from: " + from);
//            System.out.println("to: " + to);
//            System.out.println("v: " + v);
//            throw new RuntimeException(e);
//        } finally {
//            unlock();
//        }
//    }
//
//    public Long mark(String id, int from, int to, Mark mark) {
//        try {
//            lock();
//            Document document = functional.html.clone(__document);
//            Element element = document.getElementById(id);
//            if(element != null) {
//                from = functional.html.index(element, from);
//                to = functional.html.index(element, to);
//                if(from == -1) {
//                    from += 1;
//                    to += 1;
//                }
//                if(functional.html.is.block(element)) {
//                    Triple<Element, Integer, Integer> found = functional.html.adjust.find(element, from);
//                    if(functional.tuple.exist(found)) {
//                        element = found.first();
//                        from = from - found.second();
//                        to = to - found.second();
//                    } else {
//                        throw new RuntimeException("");
//                    }
//                }
//                System.out.println("mark");
//                System.out.println(element);
//                functional.html.mark(element, from, to, mark);
//                System.out.println(element);
//            } else {
//                throw new RuntimeException("");
//            }
//            __document = document;
//            return ++__version;
//        } catch(Exception e) {
//            throw new RuntimeException(e);
//        } finally {
//            unlock();
//        }
//    }
//
//    public Long unmark(String id, int from, int to, Mark mark) {
//        try {
//            lock();
//            Document document = functional.html.clone(__document);
//            Element element = document.getElementById(id);
//            if(element != null) {
//                from = functional.html.index(element, from);
//                to = functional.html.index(element, to);
//                if(from == -1) {
//                    from += 1;
//                    to += 1;
//                }
//                if(functional.html.is.block(element)) {
//                    Triple<Element, Integer, Integer> found = functional.html.adjust.find(element, from);
//                    if(functional.tuple.exist(found)) {
//                        element = found.first();
//                        from = from - found.second();
//                        to = to - found.second();
//                    } else {
//                        throw new RuntimeException("");
//                    }
//                }
//                System.out.println("unmark");
//                System.out.println(element);
//                functional.html.unmark(element, from, to, mark);
//                System.out.println(element);
//            } else {
//                throw new RuntimeException("");
//            }
//            __document = document;
//            return ++__version;
//        } catch(Exception e) {
//            throw new RuntimeException(e);
//        } finally {
//            unlock();
//        }
//    }
//
//    public Long unaround(String id, int from, int to, DocumentRemoteLine prev) {
//        try {
//            lock();
//            System.out.println("= unaround =====================================");
//            Document document = functional.html.clone(__document);
//            Element element = functional.html.get(document, id, prev);
//            if(element != null) {
//                System.out.println("original: " + element);
//                List<Element> elements = functional.html.unaround(element, from, to);
//                if(functional.list.size(elements) == 1) {
//                    element = functional.list.begin(elements);
//                    element.attr("id", id);
//                } else {
//                    throw new RuntimeException("");
//                }
//                for(Element e : elements) {
//                    System.out.println("output: " + e);
//                }
//            } else {
//                throw new RuntimeException("");
//            }
//            __document = document;
//            return ++__version;
//        } catch(Exception e) {
//            throw new RuntimeException(e);
//        } finally {
//            unlock();
//        }
//    }
//
//    public Long around(String id, int from, int to, Mark mark, DocumentRemoteLine prev) {
//        try {
//            lock();
//            System.out.println("= around =======================================");
//            Document document = functional.html.clone(__document);
//            Element element = functional.html.get(document, id, prev);
//            System.out.println("original: " + element);
//            if(functional.string.empty(mark.id())) {
//                mark.id(id);
//            }
//            element = functional.html.around(element, from, to, mark);
//            System.out.println("output: " + element);
//            __document = document;
//            return ++__version;
//        } catch(Exception e) {
//            throw new RuntimeException(e);
//        } finally {
//            unlock();
//        }
//    }
//
//    public DocumentRemoteRoot(String id) {
//        __id = id;
//    }
}
