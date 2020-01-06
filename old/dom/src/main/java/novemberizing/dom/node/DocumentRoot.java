package novemberizing.dom.node;

import novemberizing.dom.Node;
import novemberizing.dom.spec.DocumentRootSpec;

public class DocumentRoot extends Node {

    public DocumentRoot(DocumentRootSpec spec) {
        super(spec.name());
    }
}
