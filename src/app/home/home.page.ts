import { Component, OnInit } from '@angular/core';
import { EspService } from '../services/esp.service';
import { LetrasPipe } from '../letras.pipe';

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage implements OnInit {

  leds = [];
  list:any = [];
  int:any = [];
  conditions:any = [];

  intensidad:any

  constructor( private _esps:EspService){
    // this._esps.setStates()
    // .subscribe(data => {
    //   this.leds = data;
    // });
    this._esps.getList().subscribe(
      data => {
        this.list = data;
      }
    );
    this._esps.getIntensity().subscribe(
      data => {
        this.int = data;
        this.intensidad = data[0].payload.val()
      }
    );
    this._esps.getConditions().subscribe(
      data => {
        this.conditions = data;
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

  change(item:any, intensidad:any){
    this._esps.updateInt(item.key, intensidad)
  }
  

}
