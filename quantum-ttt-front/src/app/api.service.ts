import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { TestObj } from 'src/model/test_obj';

@Injectable({
  providedIn: 'root'
})
export class ApiService {

  address: string;

  constructor (private http: HttpClient) {
    this.address = 'http://localhost:8888/';
  }

  getCountries(){
    return this.http.get<TestObj>(this.address + 'sth'); 
    }

  urlHead(id: number) {
    return this.address + id.toString() + '/';
  }

  
  entangle(id: number, x: number, y: number) {
    let path = 'entangle/' + x.toString() + '/' + y.toString();
    return this.http.get<TestObj>(this.urlHead(id) + path);
  }

  restart(id: number, size: number) {
    let path = 'restart/' + size.toString();
    return this.http.get<TestObj>(this.urlHead(id) + path);
  }

  colapse(id: number, idx: number, tic: string) {
    let path = 'colapse/' + idx.toString() + '/' + tic[0] + '/' + tic.slice(1);
    return this.http.get<TestObj>(this.urlHead(id) + path);
  }
}
