package novemberizing.html;

import org.jsoup.nodes.Node;

public interface Visitor { boolean on(Node node, int depth); }
