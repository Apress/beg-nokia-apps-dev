(function(){Nokia.TemplateDefault=Nokia.Template.extend({footerIconicMenu:null,initialize:function(b){var a=this;var c={showFirstView:true};a.options=jQuery.extend(c,b);a._super.apply(a,[a.options]);a.viewManager=b.viewManager;if(!a.options.showSoftKeys&&window.menu){menu.hideSoftkeys()}if(a.options.header){a.setHeader(Nokia.dom.parseHTML('<div class="nokia-template-header"></div>'));a.options.header.element=a.getHeader();a.headerTopBar=new Nokia.TopBar(a.options.header);Nokia.dom.append(a.getHeader(),a.headerTopBar.getWrapper());Nokia.dom.append(a.getContainer(),a.getHeader())}a.setContent(Nokia.dom.parseHTML('<div class="nokia-template-content"></div>'));Nokia.dom.append(a.getContainer(),a.getContent());if(a.options.footer){a.setFooter(Nokia.dom.parseHTML('<div class="nokia-template-footer"></div>'));a.options.footer.element=Nokia.dom.parseHTML("<div></div>");a.footerIconicMenu=new Nokia.IconicMenu(a.options.footer);Nokia.dom.append(a.getFooter(),a.footerIconicMenu.getWrapper());Nokia.dom.append(a.getContainer(),a.getFooter())}else{a.getContent().addClass("nokia-template-content-no-footer")}a.views=a.viewManager.getViews();jQuery.each(a.views,function(e,d){d.setTemplate(a);d._renderUI(a.getContent())});a.viewManager.hideAll();if(a.options.showFirstView){a.viewManager.show(a.views[0])}},setSoftKeysItems:function(b){var a=this;if(window.menu){menu.clear();jQuery.each(b,function(c,e){var d=new MenuItem(e.label,c);d.onSelect=e.callback;menu.append(d)})}},getViewManager:function(){var a=this;return a.viewManager},getHeaderTopBar:function(){var a=this;return a.headerTopBar},getFooterIconicMenu:function(){var a=this;return a.footerIconicMenu}})})();