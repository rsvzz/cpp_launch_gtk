  #pragma once
  #include <glibmm-2.68/glibmm/object.h>
  class ModelItemColumn : public Glib::Object
  {
  public:
    unsigned int col_id;
    Glib::ustring col_name;
    short m_col_number;
    int m_col_percentage;

    static Glib::RefPtr<ModelItemColumn> create(unsigned int col_id,
      const Glib::ustring& col_name)
    {
      return Glib::make_refptr_for_instance<ModelItemColumn>(
        new ModelItemColumn(col_id, col_name));
    }

  protected:
    ModelItemColumn(unsigned int col_id, const Glib::ustring& col_name)
    : col_id(col_id), col_name(col_name)
    {

    }
  };
