// Initial data for exchange rates
var exchangeRates = {
  "disclaimer": "Usage subject to terms: https://openexchangerates.org/terms",
  "license": "https://openexchangerates.org/license",
  "timestamp": 1534107604,
  "base": "USD",
  "rates": {
    "BTC": 0.000157753542,
    "CAD": 1.316853,
    "EUR": 0.879353,
    "JPY": 110.46550427,
    "USD": 1,
  }
};

var $currSelect = $("#toCurrency");
$(document).ready(function() {
    $currSelect.html("<option value='' disabled selected>Select currency</option>");
    for (var i in exchangeRates.rates)
        $currSelect.append("<option value='" + i + "'>" + allCurrencies[i] + " (" + i + ")</option>");
});

$currSelect.change(function() {
    $("#resultCurrency").val((exchangeRates.rates[$(this).val()] * $("#usdInput").val()).toFixed(2));
    $("#resultLabel").text(allCurrencies[$(this).val()] + " (" + $(this).val() + ")");
});

var $updateRates = $("#updateRates");
$updateRates.click(function() {
    exchangeRates = JSON.parse($("#exchangeRates").text());
    $currSelect.html("<option value='' disabled selected>Select currency</option>");
    for (var i in exchangeRates.rates)
        $currSelect.append("<option value='" + i + "'>" + allCurrencies[i] + " (" + i + ")</option>");
    $("#resultLabel").text("To Currency ():");
    $("#resultCurrency").val("---.--");
});