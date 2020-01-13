export default class Matrix
{
  constructor(value)
  {
    if(value && !(value instanceof Array))
    {
      throw new Error();
    }
    this.value_ = value || null;
  }

  at(i)
  {
    if(!this.value_)
    {
      throw new Error();
    }
    return this.value_[i];
  }

  len()
  {
    if(!this.value_)
    {
      throw new Error();
    }
    return this.value_.length;
  }
}

// TEST

let o = new Vector([1, 2]);
console.log(o);
console.log(o.len());

try {
  o = new Vector(1);
} catch(e) {
  console.log('support');
}
