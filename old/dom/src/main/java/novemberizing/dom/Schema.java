package novemberizing.dom;

import com.google.gson.annotations.Expose;
import novemberizing.dom.spec.DocumentRootSpec;
import org.jsoup.nodes.Element;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Schema {

    private static Schema __default;

    static {
        __default = new Schema();
    }

    public static Schema get(){ return __default; }


    @Expose protected DocumentRootSpec root;
    @Expose protected Map<String, Spec> specs;
    @Expose protected Map<String, List<Spec>> map;  // TODO NAMING

    public DocumentRootSpec root() {
        return root;
    }

    public Spec get(Element element) {
        if(element != null) {
            List<Spec> list = functional.map.get(map, element.nodeName());
            if(functional.list.exist(list)) {
                for(Spec spec : list) {
                    if(spec != null) {
                        if(spec.match(element)) {
                            return spec;
                        }
                    } else {
                        throw functional.exception.on(null, element, list, spec);
                    }
                }
                return null;
            } else {
                System.out.println(element.nodeName());
                throw functional.exception.on(null, element, list);
            }
        } else {
            throw functional.exception.on(null, (Element) null);
        }
    }

    public Schema() {
        this.root = new DocumentRootSpec();
        this.specs = new HashMap<>();
        this.specs.put(Spec.h1.name(), Spec.h1);
        this.specs.put(Spec.h2.name(), Spec.h2);
        this.specs.put(Spec.h3.name(), Spec.h3);
        this.specs.put(Spec.h4.name(), Spec.h4);
        this.specs.put(Spec.h5.name(), Spec.h5);
        this.specs.put(Spec.h6.name(), Spec.h6);
        this.specs.put(Spec.p.name(), Spec.p);
        this.specs.put(Spec.span.name(), Spec.span);
        this.specs.put(Spec.pre.name(), Spec.pre);
        this.specs.put(Spec.code.name(), Spec.code);
        this.specs.put(Spec.blockquote.name(), Spec.blockquote);
        this.map = new HashMap<>();
        for(Spec spec : specs.values()) {
            map.put(spec.name(), functional.list.gen(spec));
        }
    }
}
