/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import line from '../line';

export default class service extends line {
    constructor(length, data){
        super(length, data);
        this.type = 'service';
        /**
         * When the grammar indicate '_PKT-LINE(...)_',
         * unless otherwise noted the usual _pkt-line LF_ rules apply:
         * the sender should include a _LF_, but receiver must not complain if it is not present.
         */
        if(data[data.length - 1] === '\n') {
            this.name = data.slice(10, -1);
        } else {
            this.name = data.slice(10);
        }
    }
}
