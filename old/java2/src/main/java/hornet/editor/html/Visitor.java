package hornet.editor.html;

import org.jsoup.nodes.Node;

public interface Visitor { boolean on(int start, int end, int depth, Node node); }
