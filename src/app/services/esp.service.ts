import { Injectable } from '@angular/core';
import { AngularFirestore, AngularFirestoreCollection,  } from 'angularfire2/firestore';
import { AngularFireDatabase, AngularFireList } from 'angularfire2/database';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';

@Injectable({
  providedIn: 'root'
})
export class EspService {

  listRealTime:AngularFireList<any>;

  private itemsCollection: AngularFirestoreCollection<any>;
  public states = [];

  constructor(private afs: AngularFirestore, private fbRT:AngularFireDatabase) {}

  // Cloud Firestore
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

  // =========================== //

  // Realtime Database
  getList(){
    return this.fbRT.list('/').snapshotChanges().pipe(
      map( item => {
        return item
      })
    );
  }

  updateList(item:any, status:any){
    const status$ = status.toString();
    const item$ = item.toString();
    // console.log(status$, item$);
    this.fbRT.object(item$).set(status$);
  }

}
