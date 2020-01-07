/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import line from '../line';

export default class empty extends line {
    constructor(length) {
        super(length, undefined);
        this.type = 'empty';
    }
}
