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

## Auto split column - params/config

* amounts (same afferent date for all invoices!! same units!)
  * invoice1, fraction1
  * invoice2, fraction2
* splits
  * commons (divby, percent)
  * counted (divby, [units invoice])
  * divided (divby)

## UX functionalities

* edit asoc
  * header, footer
  * persons: pres, cenz, adm
* sheet
  * add/remove apart (owner, lodger)
  * add/remove input/div col
  * add/remove output col: manual / auto(params)
  * edit invoices
* view settings
  * show/hide columns
  * grouping columns
* more
  * printing
  * colors, hints, warnings
  * override input value for specific output/split
  
## QT stuff
  
* qt property browser / widget
  * https://github.com/qtproject/qt-solutions/tree/master/qtpropertybrowser
  * https://github.com/commontk/QtPropertyBrowser
  * https://www.codeproject.com/Articles/5256485/QtTreePropertyBrowser-vs-PropertyGrid-Application
  * https://github.com/qtinuum/QtnProperty
* docking
  * https://marketplace.qt.io/collections/most-popular/products/advanced-docking-system
  
