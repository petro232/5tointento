import { Injectable } from '@angular/core';
import { AngularFirestore, AngularFirestoreCollection,  } from 'angularfire2/firestore';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';

@Injectable({
  providedIn: 'root'
})
export class EspService {

  private itemsCollection: AngularFirestoreCollection<any>;
  public states = [];

  constructor(private afs: AngularFirestore) {}

  setStates() {
    this.itemsCollection = this.afs.collection<any>('leds', ref => ref);
    return this.itemsCollection.valueChanges().pipe(
      map( (states) => {
        this.states = [];
        for( let state of states){
          this.states.unshift(state);
        }
        return this.states
      })
    )
  }

  updateLedStatus(data) {
    return this.afs.collection("leds").doc(data.name.toLowerCase()).set({name: data.name, status: data.status})
 }



}
