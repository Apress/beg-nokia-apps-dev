/* ============================================================================
* Copyright Â© 2010 Nokia. All rights reserved.
* This material, including documentation and any related computer
* programs, is protected by copyright controlled by Nokia. All
* rights are reserved. Copying, including reproducing, storing,
* adapting or translating, any or all of this material requires the
* prior written consent of Nokia. This material also contains
* confidential information which may not be disclosed to others
* without the prior written consent of Nokia.
* ============================================================================*/

// Feed update broker.
var feedUpdateBroker = null;

// Feed item control pool.
var feedItemControlPool = [];

// Feed name, URL
var feedURL="http://earthquake.usgs.gov/earthquakes/catalogs/1day-M2.5.xml";
var feedName="M2.5 Quakes";

//view manager
var viewManager;

/**
* Initialization function
*/
function init()
{
	NOKIA_PATH_JAVASCRIPT = 'lib/guarana/lib/';

	NOKIA_PATH_STYLE_ROOT = 'lib/guarana/themes/nokia/base/';
		
	Nokia.use('template-default', 'accordion', createViewManager);		
}

/**
* Creates view manager with UI components
*/
function createViewManager() 
{						
	// Global Default Floating Menu 				
	window.floatingMenu = new Nokia.FloatingMenu({
		autoRender: false,
		element: '.nokia-template-header-icon-menu',
		elementHoverClass: 'nokia-template-header-icon-menu-hover',
		offsetTop: 60,
		items: [
			{label: 'About', callback: function() { viewManager.show(1) }},
			]
	});
		
	var defaultTopItems = [
		{classname: 'nokia-template-header-icon-home', pressedStateClass: 'nokia-template-header-icon-hover',
		callback: function() {
			viewManager.show(0);
		}},
		{classname: 'nokia-template-header-icon-separator', navigable: false },
		{classname: 'nokia-template-header-icon-menu', callback: function() { floatingMenu.render().toggle() } },
		{classname: 'nokia-template-header-icon-separator', navigable: false },
		{classname: 'nokia-template-header-title', label: '' },
                {classname: 'nokia-template-header-icon-separator-right', navigable: false },
                {classname: 'nokia-template-header-icon-close', pressedStateClass: 'nokia-template-header-icon-hover',
		callback: function() {
				window.close();
			}},
		];
	
	//Feeds view	
	var FeedsView = Nokia.View.extend({
		/*
		* Lifecycle
		*/
		init: function() {
			updateFeed();			
		},
		
		renderUI: function() {
				this._viewHeader = Nokia.dom.parseHTML('<div class="widget-view">'+
														'<div id="accordion"></div>'+
														'</div>');
				Nokia.dom.append(this.getContainer(), this._viewHeader);
		},
		
		bindUI: function() {				
			this._viewHeader.click(function() {
			});	
		},
			
		syncUI: function() {
			this._viewHeader.css('color', 'red');
		},
			
		show: function() {
				if (feedName==null){
					viewManager.show(1);
				}
			var template = this.getTemplate();
			var topBar = template.getHeaderTopBar();
				
			floatingMenu.destroy();
				
			floatingMenu = new Nokia.FloatingMenu({
				autoRender: false,
				element: '.nokia-template-header-icon-menu',
				elementHoverClass: 'nokia-template-header-icon-menu-hover',
				offsetTop: 60,
				items: [
					{label: 'About', callback: function() { viewManager.show(1) }},
                                        {label: 'Refresh', callback: function() { window.location.reload(); }}
					]
			});
				
			defaultTopItems[2] = {
				classname: 'nokia-template-header-icon-menu',
				callback: function() {
					floatingMenu.render().toggle();
				}
			};
				
			defaultTopItems[4] = {
				classname: 'nokia-template-header-title',
				label: feedName
			};
				
			defaultTopItems[6] = {
				classname: 'nokia-template-header-icon-close',
				pressedStateClass: 'nokia-template-header-icon-hover',
				callback: function() {
					window.close();
				}
			};
				
			topBar.setItems(defaultTopItems);
				
			this.getContainer().show();
			}
		});
	
	//About view	
	var AboutView = Nokia.View.extend({
		/*
		* Lifecycle
		*/
		init: function() {					
			},

		renderUI: function() {
			this._viewHeader = Nokia.dom.parseHTML('<div id="about-view" class="widget-view">'+
                        '<p class="nokia-view-header">Shake on the Web by Zucker and Rischpater' + '</p><br>'+
                        '<p class="nokia-view-header">This app includes software licensed from Nokia &copy 2010' + '</p>'+
                        '</div>');
				
			Nokia.dom.append(this.getContainer(), this._viewHeader);
		},
		
		bindUI: function() {	
			this._viewHeader.click(function() {
			});		
		},
			
		syncUI: function() {
			this._viewHeader.css('color', 'blue');
		},
			
		show: function() {
			var template = this.getTemplate();
			var topBar = template.getHeaderTopBar();
				
			floatingMenu.destroy();
				
			floatingMenu = new Nokia.FloatingMenu({
				autoRender: false,
				element: '.nokia-template-header-icon-menu',
				elementHoverClass: 'nokia-template-header-icon-menu-hover',
				offsetTop: 60,
				items: [
					{label: 'Show Quakes', callback: function() { viewManager.show(0) }},
					]
				});
				
			defaultTopItems[2] = {
				classname: 'nokia-template-header-icon-menu',
				callback: function() {
					floatingMenu.render().toggle();
				}
			};
				
			defaultTopItems[4] = {
				classname: 'nokia-template-header-title',
				label: 'About'
			};
				
			defaultTopItems[6] = {
				classname: 'nokia-template-header-icon-back',
				pressedStateClass: 'nokia-template-header-icon-hover',
				callback: function() {
					viewManager.back();
				}
			};
				
			topBar.setItems(defaultTopItems);
				
			this.getContainer().show();
			}
		});
		
	viewManager = new Nokia.ViewManager({
		show: function(view) {
			}
		});
		
	viewManager.add(new FeedsView());
	viewManager.add(new AboutView());
	
	var templateDefault = new Nokia.TemplateDefault({
		viewManager: viewManager,
		header: {
			items: [] // They are already set in each view
		},
	});				
}

/**
 * Schedules an immediate feed update.
 */ 
function updateFeed() 
{
	// fetch the feed from the specified URL
    feedUpdateBroker = new FeedUpdateBroker();
    feedUpdateBroker.fetchFeed(feedURL, feedUpdateCompleted);
}

/**
 * Callback function that gets called when a feed update has completed.
 * @param event
 */ 
function feedUpdateCompleted(event)
{	

	if (event.status == "ok") {
		var notice=document.getElementById('notice');
		notice.style.visibility='hidden';
		
		setFeedItems(event.items);
		feedUpdateBroker = null;
			
	}else{
		$('#accordion').children().remove();
		showNotification(2000, "Error while updating feed!<br/>(check network settings)");
	}
}	
	
/**
 * Sets feed items.
 * @param items
 */ 
function setFeedItems(items)
{
		// start by removing all current feed items
		$('#accordion').children().remove();
		
		// create new feed items and add them to the main view
		// use feed item pool to recycle controls
		for (var i = 0; i < items.length; i++) 
		{
			var item = items[i];
			$('#accordion').append('<a href="javascript:void(0);">'+item.title+'</a>');		
			$('#accordion').append(getContentHTMLForFeedItem(item));		
		}
				var accordion = new Nokia.Accordion({
			element: '#accordion',
			collapsible: true,
			multiple: true,
			closed: true,
			toggle: function(event, header, content) {

			},
			create: function() {

			},
			open: function(event, header, content) {

			},
			close: function(event, header, content) {

			}
		});	
	}
	
/**
 * Returns the content HTML for a feed item.
 * @param item
 */ 
function getContentHTMLForFeedItem(item) 
{
    var buf = "";
    buf += "<div>";
	
    // item date
    if (item.date != null) {
        buf += "<div>" + item.date + "</div>";
    }
    
    // item description
    //if (item.description != null) {
	if (item.imgurl != null) {

		strright = item.imgurl.substr(4);

		buf += "<div>" + "<img class='quakeImage' " + strright + "</div>";

    }

    buf += "</div>";
    return buf;
}



