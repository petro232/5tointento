import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'letras'
})
export class LetrasPipe implements PipeTransform {

  transform(value: any): any {
    if(value == 'banio'){
      return 'baño';
    } else {
      return value
    }
  }

}
