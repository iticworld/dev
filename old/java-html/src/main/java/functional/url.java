package functional;

import java.net.MalformedURLException;
import java.net.URL;

public class url {
    public static URL from(String v){
        try {
            return new URL(v);
        } catch (MalformedURLException e) {
            e.printStackTrace();
            throw new RuntimeException("");
        }
    }
}
