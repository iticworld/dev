package functional;

import novemberizing.dom.Node;
import novemberizing.dom.Sample;
import novemberizing.dom.Schema;

import novemberizing.dom.Spec;
import novemberizing.dom.node.DocumentRoot;
import novemberizing.dom.spec.DocumentRootSpec;

import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.nodes.TextNode;

import java.util.List;

public class dom {
    public static DocumentRoot load(String html, Schema schema) {
        if(schema != null) {
            Document document = functional.html.load(html);
            DocumentRoot root = functional.dom.generate.root(schema.root());
            functional.dom.load(root, document.body(), schema);
            System.out.println(functional.json.to(root));
            return root;
        } else {
            throw functional.exception.on(null, html, (Schema) null);
        }
    }

    public static Node load(Node node, Element element, Schema schema) {
        if(node != null && element != null && schema != null) {
            List<Element> children = functional.html.children(element);
            if(functional.list.exist(children)) {
                for(Element child : children) {
                    if(child != null) {
                        Spec spec = schema.get(child);
                        if(spec != null) {
                            node.add(functional.dom.load(functional.dom.generate.node(node, spec), child, schema));
                        } else {
                            throw functional.exception.on(null, node, element, schema);
                        }
                    } else {
                        throw functional.exception.on(null, node, element, schema);
                    }
                }
            } else {
                if(element.childNodeSize() > 0 && element.hasText()) {
                    if(element.childNodeSize() == 1) {
                        TextNode n = (TextNode) functional.list.begin(element.childNodes());
                        node.value(n.getWholeText());
                    } else {
                        throw new RuntimeException("");
                    }
                }
            }
            return node;
        } else {
            throw functional.exception.on(null, node, element, schema);
        }
    }

    public static class generate {
        public static DocumentRoot root(DocumentRootSpec spec) {
            if(spec != null) {
                return new DocumentRoot(spec);
            } else {
                throw functional.exception.on(null, (DocumentRootSpec) null);
            }
        }

        public static Node node(Node parent, Spec spec) {
            return new Node(parent, spec);
        }
    }

    public static void main(String[] args) {
        functional.json.init(o -> {
            o.setPrettyPrinting();
        });

        functional.dom.load(Sample.html(), Schema.get());
    }
}
