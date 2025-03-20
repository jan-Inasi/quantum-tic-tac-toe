import { Component, OnInit } from '@angular/core';
import {ApiService} from './api.service';
import { TestObj } from 'src/model/test_obj';


@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  countryData: TestObj;
  title: String;
  constructor(private api:ApiService) {
    // this.countryData = {nothing: "test", move_type: "", player: "", tic: "", cycle: ""};
    this.title = "QuantumTTT";
  }

  ngOnInit() {
  //   this.api.getCountries().subscribe((data)=>{ 
  //     this.countryData = data;
  //     console.log(data);
  // });
  }
}
