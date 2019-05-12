import { Component, OnInit } from '@angular/core';
import { EspService } from '../services/esp.service';

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage implements OnInit {

  leds = [];

  list:any = [];

  constructor( private _esps:EspService){
    this._esps.setStates()
    .subscribe(data => {
      this.leds = data;
    });

    this._esps.getList().subscribe(
      data => {
        this.list = data;
      }
    );
  }

  ngOnInit(){}

  onClick(led){
    this._esps.updateLedStatus(led);
  }

  clickList(item){
    this._esps.updateList(item.key, item.payload.val())
  }
  

}
