package novemberizing.html.server;

import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.nodes.Node;
import org.jsoup.nodes.TextNode;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */
public class DocumentRemoteObject extends novemberizing.Lock {
    private static Element __load(Document document, String id) {
        if(document == null || functional.string.empty(id)) {
            throw new RuntimeException("invalid parameter exception");
        }
        Element element = document.getElementById(id);
        if(element == null) {
            throw new RuntimeException("not found object exception");
        }
        return element;
    }

    private static Element __load(Document document, String id, int index) {
        if(index < 0) {
            throw new RuntimeException("invalid parameter exception");
        }
        return __load(document, id);
    }

    private static Element __load(Document document, String id, boolean clone) {
        return clone ? functional.html.clone(__load(document, id)) : __load(document, id);
    }

    private static Element __load(Document document, String id, int index, boolean clone) {
        return clone ? functional.html.clone(__load(document, id, index)) : __load(document, id, index);
    }

    private Document __document = null;
    private Long __version = null;

    public Long insert(String id, int index, String text) {
        if(functional.string.empty(text)) {
            throw new RuntimeException("invalid parameter exception");
        }
        return insert(id, index, new TextNode(functional.html.str(text)));
    }

    public Long insert(String id, int index, Node node) {
        if(node == null) {
            throw new RuntimeException("invalid parameter exception");
        }
        Long version = null;
        try {
            lock();
            Element element = __load(functional.html.clone(__document), id, index);
            functional.html.insert(element, index, node);
            version = (++__version);
        } catch(Throwable e) {
            e.printStackTrace();
        } finally {
            unlock();
        }
        return version;
    }
}
