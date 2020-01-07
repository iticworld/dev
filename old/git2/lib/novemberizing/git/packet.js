/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import line from './line';
import empty from './lines/empty';
import service from './lines/service';
import flush from "./lines/flush";
import delimiter from "./lines/delimiter";

export default class packet {
    /**
     *
     * @param s {String} response text
     */
    static parse(s) {
        if(s.match(/^[0-9a-f]{4}#/)) {
            let start = 0;
            let length = 0;
            let lines = [];

            while(start < s.length) {
                length = parseInt('0x' + s.slice(start, start + 4));
                if(length === 0) {
                    lines.push(new flush(length));
                    start += 4;
                } else if(length === 1) {
                    lines.push(new delimiter(length));
                    start += 4;
                } else if(length === 4) {
                    lines.push(new empty(length, new empty(length)));
                    start += length;
                } else if(length > 4) {
                    let data = s.slice(start + 4, start + length);
                    if(data.match(/^# service=/)) {
                        lines.push(new service(length, data));
                    } else {
                        lines.push(new line(length, data));
                    }
                    start += length;
                } else {
                    throw new Error('unsupported length');
                }
            }
            return lines;
        } else {
            throw new Error('s.match(/^[0-9a-f]{4}#/) === false');
        }
    }
}
