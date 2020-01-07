/**
 *
 * @author novemberizing <novemberizing@gmail.com
 * @since 0.0.1
 */

import { TextEncoder } from "text-encoding";
import base64js from "base64-js";

export default class base64 {
    /**
     * encode string to base64
     *
     * @param str {string} original string
     * @param encoding {string} encoding type string
     * @returns {string} encoded string
     */
    static encode(str, encoding = 'utf-8'){
        let bytes = new TextEncoder(encoding).encode(str);
        return base64js.fromByteArray(bytes);
    }
}