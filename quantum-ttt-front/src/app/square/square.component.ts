// import { ValueConverter } from '@angular/compiler/src/render3/view/template';
import { Component, Input, OnInit, HostBinding } from '@angular/core';
import { SquareObj } from '../../model/square_obj';

@Component({
  selector: 'app-square',
  template: `
    <button class={{classes}}> {{formatted_tics}} </button>
  `,
  styles: [`
  button {
    width: 100%;
    height: 100%;
    font-size: 5em !important;
    background-color: var(--color);
    color: white;
  }
  
  .colapsed {
    font-size: 15em !important;
  }

  .to-colapse {
    background-color: blue;
  }

  .last-idx {
    background-color: darkblue;
  }
  `]
})

export class SquareComponent {

  tics: string;
  @Input() value: SquareObj;
  @Input() col_last: boolean;
  @Input() to_colapse: boolean;

  get classes() {
    let class_names = "";
    if (this.value.is_colapsed)
      class_names += "colapsed ";
    if (this.to_colapse)
      class_names += "to-colapse ";
    if (this.col_last)
      class_names += "last-idx ";
    
      return class_names;
  }

  get formatted_tics() {
    if (this.value.is_colapsed)
      return this.value.tics.toUpperCase();
      return this.value.tics
  }

}
