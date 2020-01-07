package novemberizing.log;

public class Type {
    public static final int ERROR       = 0x00000001 <<  1;
    public static final int WARNING     = 0x00000001 <<  2;
    public static final int CAUTION     = 0x00000001 <<  3;
    public static final int NOTICE      = 0x00000001 <<  4;
    public static final int INFORMATION = 0x00000001 <<  5;
    public static final int DEBUG       = 0x00000001 <<  6;
    public static final int VERBOSE     = 0x00000001 <<  7;
    public static final int FLOW        = 0x00000001 <<  8;

    public static final int ALL         = 0xFFFFFFFF;
    public static final int NONE        = 0x00000000;
}
