# TODOs

## Invoice fields

* title
* issuer
* afferent date
* total units
* sum
* estimated/final
* proforma ref: optional, for final only

Sample:
* estimated Ie:  p(Ie)..p(Ie)..p(Ie).....p(If->Ie) //anticipated,...,anticipated,regularization
* final If: p(If)..p(If).....p(If) //remainder...remainder

## Auto split column

* amounts (same afferent date for all invoices!! same units!)
  * invoice1, fraction1
  * invoice2, fraction2
* splits
  * commons (divby, percent)
  * counted (divby, [units invoice])
  * divided (divby)

## UX functionalities

* edit asoc
* sheet
  * add/remove apart
  * add/remove input col
  * add/remove output col: manual / auto(params)
  * edit invoices
* view settings (grouping)
