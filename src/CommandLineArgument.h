#ifndef COMMANDLINEARGUMENT_H
#define COMMANDLINEARGUMENT_H

#include <map>
#include <string>
#include <optional>
#include <memory>


struct Converter {
    void operator()(const std::string &_in, int &_out) const;
    void operator()(const std::string &_in, double &_out) const;
    void operator()(const std::string &_in, bool &_out) const;
};

//! Класс, определяющий аргумент коммандной строки.
class CommandLineArgument: public std::enable_shared_from_this<CommandLineArgument>
{
public:
    /*!
     * \brief Конструктор.
     * \param _arg - название аргумента.
     * \param _description - описание аргумента.\
     * \throw Если не удалось преобразовать значение к типе \a T.
     */
    explicit CommandLineArgument(std::string_view _arg,
                                 std::string_view _description);

    /*!
     * \brief Задает значение аргумента.
     * \param _value - значение аргумента.
     * \return true - если удалось задать значение аргументу, иначе false.
     */
    bool setValue(const std::string &_value);
    /*!
     * \brief Возвращает значение аргумента преобразованное к типу.
     * \tparam T - тип данных, к которому необходимо преобразовать значение.
     * \tparam C - конвертер.
     * \return значение аргумента.
     * \throw Если не удалось преобразовать значение к типе \a T.
     */
    template<class T, class C = Converter>
    T to() const;
    /*!
     * \brief Проверяет установку значения аргументу.
     * \return true - если значение установлена, иначе false.
     */
    bool hasValue() const noexcept;

    /*!
     * \brief Добавляет дочерний аргумент.
     * \param _child - дочерний агрумент.
     * \return Возвращает true при успешной вставке, иначе false.
     */
    bool addChild(std::shared_ptr<CommandLineArgument> _child) noexcept;
    /*!
     * \brief Возвращает дочерний аргумент.
     * \param _view - название аргумента.
     * \return Дочерний элемент с название \a _view.
     * \throw std::out_of_range - если не удалось найти дочерний элемент.
     */
    std::shared_ptr<CommandLineArgument> child(const std::string &_arg);
    /*!
     * \brief Возвращает список дочерних аргументов.
     * \return Список дочерних аргументов.
     */
    const std::map<std::string, std::shared_ptr<CommandLineArgument>> &children() const noexcept;
    /*!
     * \brief Возвращает родительский аргумент.
     * \return Родительский аргумент.
     */
    std::weak_ptr<CommandLineArgument> parent() const noexcept;

    /*!
     * \brief Возвращает название аргумента.
     * \return Название агрумента.
     */
    std::string_view arg() const;
    /*!
     * \brief Задает название аргумента.
     * \param _arg - название аргумента.
     */
    void setArg(std::string_view _arg);

    /*!
     * \brief Возвращает описание аргумента.
     * \return Описание аргумента.
     */
    std::string_view description() const;
    /*!
     * \brief Задает описание аргумента.
     * \param _description - описание аргумента.
     */
    void setDescription(std::string_view _description);

    /*!
     * \brief Добавляет доступные для аргумента значения.
     * \param _value - значение.
     */
    void addAvailableValue(std::string_view _value,
                           std::string_view _description) noexcept;
    /*!
     * \brief Возвращает список доступных значений для аргумента.
     * \return Список доступных для аргумента значений.
     */
    const std::map<std::string, std::string> &availableValues() const noexcept;

private:
    //! Название аргумента.
    std::string m_arg;
    //! Описание аргумента.
    std::string m_description;
    //! Значение аргумента.
    std::optional<std::string> m_value;
    //! Доступные значения.
    std::map<std::string, std::string> m_availableValues;

    //! Родительский аргумент.
    std::weak_ptr<CommandLineArgument> m_parent;
    //! Дочерние аргументы.
    std::map<std::string, std::shared_ptr<CommandLineArgument>> m_children;

    /*!
     * \brief Задает родительский элемент.
     * \param _parent - родительский элемент.
     */
    void setParent(std::shared_ptr<CommandLineArgument> _parent);
};

template<class T, class C>
T CommandLineArgument::to() const
{
    if constexpr (std::is_same_v<T, std::string>) {
        return m_value.value();
    }
    else {
        T tmp;
        C(m_value, tmp);

        return tmp;
    }
}

#endif // COMMANDLINEARGUMENT_H
