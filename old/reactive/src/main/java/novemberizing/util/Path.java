package novemberizing.util;

import java.io.File;
import java.io.IOException;
import java.util.Collections;
import java.util.LinkedList;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 21.
 */
public class Path {
    private static final String Tag = "path";

    private final String __full;
    private LinkedList<String> __parents;
    private String __self;
    private String __name;
    private String __extension;

    public String full(){ return __full; }
    public String v(){ return __self; }
    public String name(){ return __name; }
    public String extention(){ return __extension; }
    public LinkedList<String> parents(){ return __parents; }

    public boolean mkdir(){
        String path = "/";
        for(String dir : __parents){
            path += dir;
            File f = new File(path);
            if(!f.mkdir()){
                Log.w(Tag, "f.mkdir()==false");
            }
            path += "/";
        }
        return true;
    }

    public boolean exist(){
        File f = new File(__full);
        return f.exists();
    }

    @SuppressWarnings("ResultOfMethodCallIgnored")
    public File touch() throws IOException {
        File f = new File(__full);
        mkdir();
        f.createNewFile();
        return f;
    }


    @SuppressWarnings("ResultOfMethodCallIgnored")
    public void del(){
        File f = new File(__full);
        f.delete();
    }

    public Path(String s){
        __full = s;
        __parents = new LinkedList<>();
        Collections.addAll(__parents, __full.split("[/]"));
        __self = __parents.pollLast();
        String[] splitted = __self.split("[.]");
        if(splitted.length>1){
            __extension = splitted[splitted.length-1];
            __name = __self.substring(0, __self.length() - __extension.length());
        } else {
            __extension = null;
        }
    }

    public Path(Path path){
        __full = path.__full;
        __parents = new LinkedList<>(path.__parents);
        __self = path.__self;
        __name = path.__name;
        __extension = path.__extension;
    }
}
