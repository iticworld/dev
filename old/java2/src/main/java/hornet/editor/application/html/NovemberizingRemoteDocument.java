package hornet.editor.application.html;

import hornet.editor.html.Sample;
import hornet.editor.html.server.RemoteDocument;

public class NovemberizingRemoteDocument extends RemoteDocument {
    @Override
    public void load() {
        lock();
        if(__document == null) {
            __document = functional.html.to.document(Sample.get());
            __version = 0L;
        }
        unlock();
    }

    public NovemberizingRemoteDocument(String id) {
        super(id);
    }
}
