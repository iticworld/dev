/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import base64 from './util/base64';

/**
 *
 * @param n {Number}
 * @param prefix {String}
 */
function hex(n, prefix){
    return prefix ? (prefix + n.toString(16)).slice(-prefix.length) : n.toString(16);
}

let util = {
    base64: base64,
    hex: hex
};

export default util;
