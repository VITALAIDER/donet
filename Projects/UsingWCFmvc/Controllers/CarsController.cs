using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace UsingWCFmvc.Controllers
{
    public class CarsController : Controller
    {
        // GET: First
        public ActionResult Index()
        {
            ViewBag.Title = "Rent a car system ";
            ViewBag.AllCars = "masina 1 masina 2 etc";
            return View();
        }

        // GET: First/Details/5
        public ActionResult Details(int id)
        {
            return View();
        }

        // GET: First/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: First/Create
        [HttpPost]
        public ActionResult Create(FormCollection collection)
        {
            try
            {
                // TODO: Add insert logic here

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: First/Edit/5
        public ActionResult Edit(int id)
        {
            return View();
        }

        // POST: First/Edit/5
        [HttpPost]
        public ActionResult Edit(int id, FormCollection collection)
        {
            try
            {
                // TODO: Add update logic here

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: First/Delete/5
        public ActionResult Delete(int id)
        {
            return View();
        }

        // POST: First/Delete/5
        [HttpPost]
        public ActionResult Delete(int id, FormCollection collection)
        {
            try
            {
                // TODO: Add delete logic here

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
    }
}
