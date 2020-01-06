package example.functional;

import com.google.gson.*;
import novemberizing.Listener;
import novemberizing.html.GsonDocumentSerializer;
import novemberizing.html.GsonElementSerializer;
import novemberizing.html.GsonTextNodeSerializer;
import novemberizing.tuple.Pair;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.nodes.Node;
import org.jsoup.nodes.TextNode;

import java.util.List;


public class ExampleFunctionalHTML {

    public static void main(String[] args) {
//        functional.json.init(o -> {
//            o.registerTypeAdapter(Element.class, new GsonElementSerializer());
//            o.registerTypeAdapter(TextNode.class, new GsonTextNodeSerializer());
//            o.registerTypeAdapter(Document.class, new GsonDocumentSerializer());
//        });
//
//        Document document = functional.html.from("<p>hello<br />world</p>");
//        functional.html.print(document);
//
//        document = functional.html.from("<p>hello<br />world</p><p>h<span>ello<br />w<strong>o</strong></span>rld</p>");
//        functional.html.print(document);
//
//        functional.html.traverse(functional.html.from("<p>hello<br />world</p><p>h<span>ello<br />w<strong>o</strong></span>rld</p>"),
//                                 functional.html::print);
//
//
        Document document = functional.html.from("<p>hello<br />world</p><p>h<span>ello<br />w<strong>o</strong></span>rld</p>");
        System.out.println("document: " + functional.html.to.html(document));
         int total = functional.html.length(document);
//
//        for(int i = 0; i < total; i++) {
//            Pair<Node, Integer> found = functional.html.find(document, i);
//            System.out.println("i: " + i);
//            System.out.println("index: " + found.second());
//            System.out.println("html: " + functional.html.to.string(found.first()));
//        }
//
//        for(int i = 0; i < total; i++) {
//            List<Node> nodes = functional.html.split(functional.html.front(document.body()), i);
//            System.out.println("i: " + i);
//            for(Node node : nodes){
//                System.out.println(i + ": " + functional.html.to.html(node));
//            }
//        }

        Node n = functional.html.front(document, true);
        Node parent = functional.html.parent(n, 3);
        System.out.println("n: " + functional.html.to.html(n));
        System.out.println("parent[3]: " + functional.html.to.html(parent));
        System.out.println("parent[depth]: " + functional.html.depth(parent));
        System.out.println("depth: " + functional.html.depth(n));
        n = functional.html.next(n, true);
        parent = functional.html.parent(n, 3);
        System.out.println("n: " + n);
        System.out.println("parent[3]: " + functional.html.to.html(parent));
        System.out.println("parent[depth]: " + functional.html.depth(parent));
        System.out.println("depth: " + functional.html.depth(n));
        n = functional.html.prev(n, true);
        parent = functional.html.parent(n, 2);
        System.out.println("n: " + n);
        System.out.println("parent[2]: " + functional.html.to.html(parent));
        System.out.println("depth: " + functional.html.depth(n));
        n = functional.html.back(document, true);
        parent = functional.html.parent(n, 2);
        System.out.println("n: " + functional.html.to.html(n));
        System.out.println("parent[2]: " + functional.html.to.html(parent));
        System.out.println("depth: " + functional.html.depth(n));
        n = functional.html.prev(n, true);
        parent = functional.html.parent(n, 2);
        System.out.println("n: " + n);
        System.out.println("parent[2]: " + functional.html.to.html(parent));
        System.out.println("depth: " + functional.html.depth(n));
        n = functional.html.next(n, true);
        parent = functional.html.parent(n, 2);
        System.out.println("n: " + n);
        System.out.println("parent[2]: " + functional.html.to.html(parent));
        System.out.println("depth: " + functional.html.depth(n));



//        for(int i = 0; i < total; i++) {
//            for(int j = i + 1; j < total + 1; j++) {
//                Pair<Node, Integer> found = functional.html.find(document, i, j);
//                System.out.println("i: " + i);
//                System.out.println("j: " + j);
//                System.out.println("index: " + found.second());
//                System.out.println("html: " + functional.html.to.string(found.first()));
//                System.out.println("orig: [" + functional.html.to.text(document) + "]");
//                System.out.println("text: [" + functional.string.fill(" ", found.second())
//                                             + functional.html.to.text(found.first())
//                                             + functional.string.fill(" ", total - functional.html.length(found.first()) - found.second()) + "]");
//
//            }
//        }

//        System.out.println(functional.json.from(document.body()));

//        System.out.println(functional.html.to(functional.html.from("<p>hello<br />world</p>")));
//        functional.html.traverse(functional.html.from("<p>h<span>ello<br />w<strong>o</strong></span>rld</p>"),
//                                 (start, end, depth, node) -> {
//                                     System.out.println(functional.html.to(node));
//                                     return true;
//                                 });
    }
}
